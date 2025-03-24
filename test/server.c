#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
int main(){
    struct sockaddr_in server, client;
    int sockfd, new_socket;
    char buffer [1024];
    socklen_t len =sizeof(client);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port=htons(8080);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(sockfd,(struct sockaddr *)&server, sizeof(server));
    printf("Waiting for connection\n");
    listen(sockfd, 5);
    new_socket=accept(sockfd,(struct sockaddr *)&client, &len);
    read(new_socket, buffer, sizeof(buffer));
    printf("message: %s\n",buffer);
    send(new_socket,"hello guys",10,0);
    close(new_socket);
    close(sockfd);


}