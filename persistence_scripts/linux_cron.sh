#!/bin/bash
(crontab -l 2>/dev/null; echo "@reboot /usr/bin/updater") | crontab -