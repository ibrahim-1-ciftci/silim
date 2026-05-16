# Installation

## Dependencies
- Python 3.8+ (PyQt5, cryptography, requests, psutil)
- Go 1.18+
- GCC/MinGW (for Windows dropper/payload)
- GCC, Clang (for Linux/macOS)
- Android NDK r25+ (for Android payload)
- OpenSSL (for cert generation)

## Steps
1. `pip install -r requirements.txt`
2. Generate certs: `cd c2_server/certs && ./gen_cert.sh` (Linux/macOS) or `gen_cert.bat` (Windows)
3. Build all: `python build_all.py`
4. Start C2: `cd c2_server && go run main.go`
5. Start GUI: `cd gui_panel && python main.py`
6. Deploy dropper to target and execute.