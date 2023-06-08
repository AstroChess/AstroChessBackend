#include "http_lexer.h"

#define CMD_ARG_LEN 2
#define BUFFER_SIZE 4096

class CmdArgParser {
public:
    CmdArgParser(int argc, char **argv, char *buf) {
        if(argc > CMD_ARG_LEN) { printf("Too many args\n"); exit(1); }
        else if(argc == CMD_ARG_LEN) {
            FILE *fptr = fopen(argv[1], "r");
            char c;
            int i = 0;
            while((c = fgetc(fptr)) != EOF) {
                buf[i] = c;
                i += 1;
            }
        }
        else { printf("Not enough args\n"); exit(1); }
    }
};

int main(int argc, char **argv) {
    char buf[BUFFER_SIZE];
    CmdArgParser cmd = CmdArgParser(argc, argv, buf);

    using namespace Net;
    HttpLexer::Token token = HttpLexer::Token(HttpLexer::TokenType::ACTION, "GET", 1);
    printf("{ ID: 1, %s }\n", token.to_string());

    return 0;
}
