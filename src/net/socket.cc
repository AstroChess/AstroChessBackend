#include "net.h"

using namespace Net;

Socket::Socket() {
    this->socket_desc = socket(this->domain, this->type, this->protocol);
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = INADDR_ANY;
    this->server.sin_port = htons(8080);
}

void Socket::_bind() {
    if(bind(this->socket_desc, (struct sockaddr *) &this->server, sizeof(this->server)) < 0) {
        printf("Failed to bind\n");
        exit(1);
    }
}

void Socket::_listen() {
    listen(this->socket_desc, 3);
}

void Socket::_accept() {
    int c = sizeof(struct sockaddr_in);
    this->client_sock = accept(this->socket_desc, (struct sockaddr *) &this->client, (socklen_t *) &c);
}

void Socket::_receive() {
    while((this->read_size = recv(this->client_sock, this->buffer, BUFFER_SIZE, 0)) > 0) {
        printf("%s\n", this->buffer);
    }
}

void Socket::open() {
    this->_bind();
    this->_listen();
    this->_accept();
    this->_receive();
}
