#include "net.h"

using namespace Net;

void HttpDecoder::Decode(char *src) {
    char current_token[64];
    int current_token_idx = 0;
    for(int i = 0; src[i] != 0; i++) {
        current_token[current_token_idx] = src[i];
        current_token_idx += 1;
    }
}
