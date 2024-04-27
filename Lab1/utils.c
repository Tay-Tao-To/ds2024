// In utils.c
#include "utils.h"

void send_file(int socket, const char *filename) {
    // Open the file
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Cannot open file");
        return;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    // Send the file size first
    write(socket, &filesize, sizeof(filesize));

    // Send the file content
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(socket, buffer, bytes_read, 0);
    }

    // Close the file
    fclose(file);
}

void receive_file(int socket, const char *filename) {
    // Create a file where we will save the incoming data
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Cannot create file");
        return;
    }

    // Read the file size first
    long filesize;
    read(socket, &filesize, sizeof(filesize));

    // Receive the file content
    char buffer[1024];
    long total_bytes_received = 0;
    while (total_bytes_received < filesize) {
        int bytes_received = recv(socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break; // Error or connection closed
        }
        fwrite(buffer, 1, bytes_received, file);
        total_bytes_received += bytes_received;
    }

    // Close the file
    fclose(file);
}