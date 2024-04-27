#include "file_transfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implement the SENDFILE RPC service
transferstatus * sendfile_1_svc(filechunk *chunk, struct svc_req *req) {
    static transferstatus result;
    FILE *file;

    // Open file for writing
    file = fopen(chunk->filename, "ab");
    if (!file) {
        result.success = 0;
        result.message = strdup("Could not open file for writing.");
        return &result;
    }

    // Write the data to the file
    if (fwrite(chunk->data.data_val, 1, chunk->data.data_len, file) != chunk->data.data_len) {
        result.success = 0;
        result.message = strdup("Could not write to file.");
        fclose(file);
        return &result;
    }

    fclose(file);
    result.success = 1;
    result.message = strdup("File written successfully.");
    return &result;
}

int main() {
    register SVCXPRT *transp;

    pmap_unset(FILE_TRANSFER_PROG, FILE_TRANSFER_VERS);

    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL) {
        fprintf(stderr, "cannot create udp service.\n");
        exit(1);
    }
    if (!svc_register(transp, FILE_TRANSFER_PROG, FILE_TRANSFER_VERS, file_transfer_prog_1, IPPROTO_UDP)) {
        fprintf(stderr, "unable to register (FILE_TRANSFER_PROG, FILE_TRANSFER_VERS, udp).\n");
        exit(1);
    }

    svc_run();
    fprintf(stderr, "svc_run returned\n");
    exit(1);
}