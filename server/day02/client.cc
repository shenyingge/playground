#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "util.h"
#include <iostream>

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);
    connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
    std::string line;
    while (true){
        char buf[1024];
        memset(&buf, 0, sizeof(buf));
        std::getline(std::cin, line);;
        ssize_t write_bytes = write(sockfd, buf, sizeof(buf));
        if (write_bytes == -1){
            printf("socket already disconnected\n");
            break;
        }
        memset(&buf, 0, sizeof(buf));
        ssize_t read_bytes = read(sockfd, buf, sizeof(buf));
        if (read_bytes > 0){
            printf("message from server: %s\n", buf);
        }else if(read_bytes == 0){
            printf("server socket disconnected!\n");
            break;
        }else if(read_bytes == -1){
            close(sockfd);
            errif(true, "socket read error");
        }
    }

    return 0;
}
