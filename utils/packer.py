import subprocess, sys

def upx_pack(exe_path):
    subprocess.run(["upx", "--best", "--lzma", exe_path], check=False)