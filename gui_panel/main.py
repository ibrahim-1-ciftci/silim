import sys, threading, requests
from PyQt5.QtWidgets import QApplication, QMainWindow, QTabWidget
from PyQt5.QtCore import QThread, pyqtSignal
from widgets.client_widget import ClientWidget
from widgets.command_widget import CommandWidget
from widgets.ai_widget import AIWidget
from widgets.stats_widget import StatsWidget

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("ArenkNet Control Center")
        self.setGeometry(100, 100, 1200, 800)
        self.c2_url = "https://localhost:443"
        self.init_ui()
        self.start_polling()

    def init_ui(self):
        self.tabs = QTabWidget()
        self.client_tab = ClientWidget(self.c2_url)
        self.command_tab = CommandWidget(self.c2_url)
        self.ai_tab = AIWidget(self.c2_url)
        self.stats_tab = StatsWidget(self.c2_url)
        self.tabs.addTab(self.client_tab, "Clients")
        self.tabs.addTab(self.command_tab, "Commands")
        self.tabs.addTab(self.ai_tab, "AI Reports")
        self.tabs.addTab(self.stats_tab, "Statistics")
        self.setCentralWidget(self.tabs)

    def start_polling(self):
        def poll():
            while True:
                self.client_tab.refresh()
                QThread.msleep(3000)
        threading.Thread(target=poll, daemon=True).start()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setStyleSheet(open("resources/style.qss").read())
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())