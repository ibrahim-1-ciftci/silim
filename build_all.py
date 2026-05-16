#!/usr/bin/env python3
import subprocess, os, sys

def run(cmd, cwd=None):
    print(f"[BUILD] {cmd}")
    subprocess.run(cmd, shell=True, cwd=cwd, check=True)

def main():
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    run("go build -o c2_server main.go", "c2_server")
    run("pyinstaller --onefile main.py --name gui_panel", "gui_panel")
    run("bash build_all.sh", "dropper")
    run("build.bat", "payload_windows")
    run("bash build.sh", "payload_linux")
    run("bash build.sh", "payload_macos")
    run("ndk-build", "payload_android")
    run("build.bat", "kernel_driver")
    print("[SUCCESS] All components built.")

if __name__ == "__main__":
    main()