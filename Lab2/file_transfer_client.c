#include "file_transfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file_transfer_prog_1(char *host, char *filename) {
    CLIENT *clnt;
    transferstatus  *result_1;
    filechunk sendfile_1_arg;

    clnt = clnt_create(host, FILE_TRANSFER_PROG, FILE_TRANSFER_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    // Open the file to send
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(1);
    }

    // Prepare the file chunk
    sendfile_1_arg.filename = filename;
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    sendfile_1_arg.data.data_len = fileSize;
    sendfile_1_arg.data.data_val = malloc(fileSize);
    fread(sendfile_1_arg.data.data_val, 1, fileSize, file);

    // Make the RPC call
    result_1 = sendfile_1(&sendfile_1_arg, clnt);
    if (result_1 == (transferstatus *) NULL) {
        clnt_perror(clnt, "call failed:");
    } else {
        printf("%s\n", result_1->message);
    }

    // Clean up
    free(sendfile_1_arg.data.data_val);
    fclose(file);
    clnt_destroy(clnt);
}

int main(int argc, char *argv
[]) {
    char *host;
    char *filename;

    if (argc < 3) {
        printf("usage: %s server_host filename\n", argv[0]);
        exit(1);
    }
    host = argv[1];
    filename = argv[2];

    file_transfer_prog_1(host, filename);

    exit(0);
}