#ifndef NET_HTTP_LEXER_H
#define NET_HTTP_LEXER_H

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _GLIBCXX_STDLIB_H
#include <stdlib.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

namespace Net {
namespace HttpLexer {

enum TokenType {
    ACTION,
    PATH,
    VERSION,
    HOST
};

struct Token {
    TokenType type;
    char *lexeme;
    int line;
    Token(TokenType type, const char *lexeme, int line) {
        this->type = type;
        this->lexeme = (char *) malloc(sizeof(char) * (strlen(lexeme) + 1));
        strcpy(this->lexeme, lexeme);
        this->line = line;
    }
    char * to_string();
};

}
}

#endif
