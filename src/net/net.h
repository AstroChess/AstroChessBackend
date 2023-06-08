#ifndef NET_NET_H
#define NET_NET_H

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace Net {

enum AddressFamily {
    Ipv4 = AF_INET
};

enum Protocol {
    TCP = SOCK_STREAM
};

class Socket {
    int socket_desc;
    int client_sock;
    int read_size;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char buffer[BUFFER_SIZE];
    void _bind();
    void _listen();
    void _accept();
    void _receive();
public:
    Socket(AddressFamily af, Protocol proto, int port);
    void open();
};

}

#endif
