// In utils.h
#ifndef UTILS_H
#define UTILS_H

void send_file(int socket, const char *filename);
void receive_file(int socket, const char *filename);

#endif // UTILS_H