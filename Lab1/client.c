// Client-side demonstrate Socket
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "utils.c"

#define PORT 8080

void sendFileToServer(const char* filename, int sock) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("File not found");
        return;
    }

    char buffer[1024];
    int nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        send(sock, buffer, nread, 0);
    }

    fclose(fp);
    printf("File sent successfully\n");
}

int main(int argc, char const* argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Check if the file name is provided
    if (argc < 2) {
        printf("Enter the file name as an argument\n");
        return -1;
    }

    // Function to send the file to the server
    sendFileToServer(argv[1], sock);

    close(sock);
    return 0;
}