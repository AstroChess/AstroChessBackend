#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

enum SOCKET_STATUS {
	SUCCESS,
	CREATE_FAILED,
	BIND_FAILED,
	LISTEN_FAILED,
	ACCEPT_FAILED
};

int atoi(char *str) {
	int num = 0;
	int counter = 1;
	int num_len = 0;
	for(int i = 0; str[i] != 0; i++) {
		num_len += 1;
	}
	for(int i = num_len-1; i >= 0; i--) {
		int curr = (int) str[i] - '0';
		num += curr * counter;
		counter *= 10;
	}
	return num;
}

enum SOCKET_STATUS socket_listener_open(int port) {
	int sockfd, clientfd;
	struct sockaddr_in addr, client;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) { return CREATE_FAILED; }
	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) != 0) { return BIND_FAILED; }
	if(listen(sockfd, 4) != 0) { return LISTEN_FAILED; }
	printf("Listenning for connections on port %i...\n", port);
	int len = sizeof(client);
	while(clientfd = accept(sockfd, (struct sockaddr *) &client, &len)) {
		if(clientfd < 0) { break; return ACCEPT_FAILED; }
		printf("Accepted connection\n");
	}
	return 0;
}

int main(int argc, char **argv) {
	if(argc < 2) { printf("You have to provide port argument\n"); return 1; }
	int port = atoi(argv[1]);
	switch(socket_listener_open(port)) {
		case CREATE_FAILED:
			printf("Failed to create socket\n");
			return 1;
		case BIND_FAILED:
			printf("Failed to bind socket\n");
			return 1;
		case LISTEN_FAILED:
			printf("Failed to listen on socket\n");
			return 1;
		case ACCEPT_FAILED:
			printf("Failed to accept connection\n");
			return 1;
	}

	return 0;
}
