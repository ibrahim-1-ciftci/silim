# ArenkNet Advanced RAT - Complete Academic Project

**Full-featured, cross-platform Remote Access Trojan for educational research.**

## Supported Platforms
- Windows (x86/x64) – full stealth, EDR bypass, kernel driver
- Linux (x86_64) – ptrace evasion, persistence
- macOS (x86_64/ARM64) – launchd persistence, keychain access
- Android (ARM64) – native payload, accessibility abuse

## Key Features
- Staged payload delivery (dropper + reflective loading)
- Kernel-level process/file hiding (Windows driver)
- AMSI/ETW bypass, direct syscall
- AI-based threat analysis and reporting
- Multiple persistence (WMI, schtask, crontab, launchd)
- DGA + HTTPS over CDN for C2 communication

## Quick Start
See INSTALL.md