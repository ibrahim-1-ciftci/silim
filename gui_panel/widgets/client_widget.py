from PyQt5.QtWidgets import QWidget, QVBoxLayout, QListWidget, QLabel, QListWidgetItem
import requests

class ClientWidget(QWidget):
    def __init__(self, c2_url):
        super().__init__()
        self.c2_url = c2_url
        self.layout = QVBoxLayout()
        self.label = QLabel("Connected Clients:")
        self.list = QListWidget()
        self.list.itemClicked.connect(self.on_select)
        self.layout.addWidget(self.label)
        self.layout.addWidget(self.list)
        self.setLayout(self.layout)
        self.selected_client = None

    def refresh(self):
        try:
            r = requests.get(f"{self.c2_url}/api/clients", verify=False)
            clients = r.json()
            self.list.clear()
            for c in clients:
                item = QListWidgetItem(f"{c['id']} ({c['os']} {c['arch']})")
                item.setData(1, c['id'])
                self.list.addItem(item)
        except:
            pass

    def on_select(self, item):
        self.selected_client = item.data(1)
        # notify command widget
        parent = self.parent().parent()
        cmd_tab = parent.findChild(CommandWidget)
        if cmd_tab:
            cmd_tab.set_client(self.selected_client)