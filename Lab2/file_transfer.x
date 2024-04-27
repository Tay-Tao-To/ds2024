struct filechunk {
    string filename<>;
    opaque data<>;
};

struct transferstatus {
    bool_t success;
    string message<>;
};

program FILE_TRANSFER_PROG {
    version FILE_TRANSFER_VERS {
        transferstatus SENDFILE(filechunk) = 1;
    } = 1;
} = 0x20000099;