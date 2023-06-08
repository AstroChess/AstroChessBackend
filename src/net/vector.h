#ifndef NET_VECTOR_H
#define NET_VECTOR_H

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef	_STRING_H
#include <string.h>
#endif

#ifndef _GLIBCXX_STDLIB_H
#include <stdlib.h>
#endif

template <typename T>
class Vector {
    int size;
    int capacity;
    T *data;
public:
    Vector() {
        this->data = (T *) malloc(sizeof(T) * 2);
        this->capacity = 2;
        this->size = 0;
    }
    void push(T val) {
        if((this->size + 1) == this->capacity) {
            T *new_ptr = (T *) malloc(sizeof(T) * (this->capacity * 2));
            memcpy(new_ptr, this->data, sizeof(T));
            this->data = new_ptr;
            this->capacity *= 2;
        }
        this->data[this->size] = val;
        this->size += 1;
    }
    T& operator[](const int index) {
        if(this->size <= index) {
            printf("Index %i is out of bound\n", index);
            exit(1);
        }
        return this->data[index];
    }
};

#endif
