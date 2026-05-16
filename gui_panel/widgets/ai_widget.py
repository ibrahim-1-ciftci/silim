from PyQt5.QtWidgets import QWidget, QVBoxLayout, QTextEdit, QLabel

class AIWidget(QWidget):
    def __init__(self, c2_url):
        super().__init__()
        self.c2_url = c2_url
        layout = QVBoxLayout()
        self.text = QTextEdit()
        self.text.setReadOnly(True)
        layout.addWidget(QLabel("AI Threat Reports"))
        layout.addWidget(self.text)
        self.setLayout(layout)
        # TODO: WebSocket or polling for AI reports