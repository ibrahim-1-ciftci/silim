from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel

class StatsWidget(QWidget):
    def __init__(self, c2_url):
        super().__init__()
        self.c2_url = c2_url
        layout = QVBoxLayout()
        self.label = QLabel("Statistics will appear here")
        layout.addWidget(self.label)
        self.setLayout(layout)

    def update_stats(self, clients):
        self.label.setText(f"Total clients: {len(clients)}")