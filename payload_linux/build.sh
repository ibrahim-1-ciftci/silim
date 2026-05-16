#!/bin/bash
gcc -o payload_linux main.c ptrace_evasion.c persistence.c stealth.c -static