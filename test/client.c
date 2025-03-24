#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024]="hello world";

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.0");
    server.sin_port = htons(8080);

    connect(sockfd,(struct sockaddr *)&server, sizeof(server));
    send(sockfd,buffer, sizeof(buffer),0);
    read(sockfd, buffer,sizeof(buffer));
    printf("message:%s\n",buffer);
    close(sockfd);
}