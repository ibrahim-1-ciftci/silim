import platform, psutil

class ThreatIntel:
    @staticmethod
    def is_vm():
        vm_strings = ["vbox", "vmware", "qemu", "hyperv", "docker", "kvm"]
        system = platform.platform().lower()
        return any(v in system for v in vm_strings)
    @staticmethod
    def is_debugger():
        try:
            with open("/proc/self/status") as f:
                return "TracerPid:" in f.read()
        except:
            return False