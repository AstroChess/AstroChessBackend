#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

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

int socket_listener_open(int port) {
	int sockfd;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) { return -1; }
	return 0;
}

int main(int argc, char **argv) {
	if(argc < 2) { printf("You have to provide port argument\n"); return 1; }
	int port = atoi(argv[1]);
	if(socket_listener_open(port) < 0) { return 1; }

	return 0;
}
