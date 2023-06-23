#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

enum SOCKET_STATUS {
	SUCCESS,
	CREATE_FAILED,
	BIND_FAILED,
	LISTEN_FAILED,
	ACCEPT_FAILED
};

enum HttpMethod {
	GET,
	POST,
	PUT,
	DELETE
};

const char *HttpMethodIdents[] = {
	"GET",
	"POST",
	"PUT",
	"DELETE"
};

struct HttpRequest {
	enum HttpMethod method;
	char path[16];
	char version[16];
};

void http_request_init(struct HttpRequest *hr, char *str) {
	char lexemes[3][16];
	int j = 0;
	int k = 0;
	for(int i = 0; str[i] != 0; i++) {
		if(str[i] == '\r' || str[i] == '\n') {
			lexemes[j][k] = '\0';
			j += 1;
			break;
		} else if(str[i] == ' ') {
			lexemes[j][k] = '\0';
			j += 1;
			k = 0;
		} else {
			lexemes[j][k] = str[i];
			k += 1;
		}
	}
	if(strcmp(lexemes[0], "GET") == 0) {
		hr->method = GET;
	} else if(strcmp(lexemes[0], "POST") == 0) {
		hr->method = POST;
	} else if(strcmp(lexemes[0], "PUT") == 0) {
		hr->method = PUT;
	} else if(strcmp(lexemes[0], "DELETE") == 0) {
		hr->method = DELETE;
	}
	strcpy(hr->path, lexemes[1]);
	strcpy(hr->version, lexemes[2]);
}

void http_request_print(struct HttpRequest *hr) {
	printf("{ Method: %s, Path: %s, Version: %s }\n", HttpMethodIdents[hr->method], hr->path, hr->version);
}

struct Route {
	enum HttpMethod method;
	const char *path;
	void (*func)();
};

void say_hello() { printf("Hello from route\n"); }

static struct Route Routes[] = {
	{ .method = GET, .path = "/hello", .func = &say_hello }
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
	char buf[1024];
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
		printf("Accepted connection\n");
		int valread = read(clientfd, buf, 1024);
		struct HttpRequest req;
		http_request_init(&req, buf);
		http_request_print(&req);
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
