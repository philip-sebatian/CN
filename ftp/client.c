#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

void downloadFile(int sock, char *filename) {
    char response[BUFFER_SIZE];
    recv(sock, response, BUFFER_SIZE, 0);

    if (strcmp(response, "OK") != 0) {
        printf("Server error: %s\n", response);
        return;
    }

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("File open error");
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_received;
    while ((bytes_received = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
    }

    fclose(file);
    printf("File downloaded successfully.\n");
}

void uploadFile(int sock, char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found!\n");
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(sock, buffer, bytes_read, 0);
    }

    fclose(file);
    printf("File uploaded successfully.\n");
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char command[BUFFER_SIZE], filename[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Enter command (GET/PUT) followed by filename: ");
    scanf("%s %s", command, filename);

    send(sock, command, strlen(command), 0);
    send(sock, filename, strlen(filename), 0);

    if (strcmp(command, "GET") == 0) {
        downloadFile(sock, filename);
    } else if (strcmp(command, "PUT") == 0) {
        uploadFile(sock, filename);
    }

    close(sock);
    return 0;
}
