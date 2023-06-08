#include "http_lexer.h"
#include "vector.h"

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
    HttpLexer::Scanner scanner = HttpLexer::Scanner(buf);

    Vector<int> vec = Vector<int>();
    vec.push(1);
    vec.push(2);
    vec.push(3);
    vec.push(4);
    printf("%i\n", vec[4]);

    return 0;
}
