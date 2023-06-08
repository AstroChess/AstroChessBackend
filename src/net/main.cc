#include "http_lexer.h"

int main() {
    using namespace Net;
    HttpLexer::Token token = HttpLexer::Token(HttpLexer::TokenType::ACTION, "GET", 1);
    printf("{ ID: 1, %s }\n", token.to_string());

    return 0;
}
