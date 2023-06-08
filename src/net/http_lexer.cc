#include "http_lexer.h"

using namespace Net::HttpLexer;

const char *TokenTypeIdents[] = {
    "ACTION",
    "PATH",
    "VERSION",
    "HOST"
};

char * Token::to_string() {
    char *str;
    sprintf(str, "Type: %s, Lexeme: %s, Line: %i", TokenTypeIdents[this->type], this->lexeme, this->line);
    return str;
}
