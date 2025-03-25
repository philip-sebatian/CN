#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void sendFile(int client_sock, char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        send(client_sock, "ERROR: File not found.", 22, 0);
        return;
    }
    
    send(client_sock, "OK", 2, 0);  // Send confirmation

    char buffer[BUFFER_SIZE];
    int bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(client_sock, buffer, bytes_read, 0);
    }
    
    fclose(file);
}

void receiveFile(int client_sock, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("File open error");
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_received;
    
    while ((bytes_received = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
    }

    fclose(file);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char command[BUFFER_SIZE], filename[BUFFER_SIZE];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);

    printf("FTP Server started on port %d...\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        printf("Client connected!\n");

        recv(client_sock, command, BUFFER_SIZE, 0);
        recv(client_sock, filename, BUFFER_SIZE, 0);

        if (strcmp(command, "GET") == 0) {
            sendFile(client_sock, filename);
        } else if (strcmp(command, "PUT") == 0) {
            receiveFile(client_sock, filename);
        }

        close(client_sock);
        printf("Client disconnected.\n");
    }

    close(server_sock);
    return 0;
}
