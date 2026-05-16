import subprocess, os

def build_all():
    os.chdir("../payload_windows")
    subprocess.run("build.bat", shell=True)
    os.chdir("../payload_linux")
    subprocess.run("bash build.sh", shell=True)
    # ... others

if __name__ == "__main__":
    build_all()