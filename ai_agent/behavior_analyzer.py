class BehaviorAnalyzer:
    def __init__(self):
        self.commands = []
    def add_command(self, cmd):
        self.commands.append(cmd)
    def analyze(self):
        return len(self.commands) > 100