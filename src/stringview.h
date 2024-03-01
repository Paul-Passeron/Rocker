#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <stddef.h>
#include <string.h>
#include "../RockerAllocator/alloc.h"

typedef struct string_view {
    char *data;
    size_t length;
}string_view;

string_view sv_from_parts(char *data, size_t length){
    return (string_view){
        data, length
    };
}

string_view sv_from_cstr(char *s){
    if(s == NULL) return {0};
    return sv_from_parts(s, strlen(s));
}

char *string_of_sv(string_view s){
    char *data = (char*)allocate_compiler_persistent(s.length + 1);
    memcpy(data, s.data, s.length);
    data[s.length] = 0;
    return data;
}   

#endif // STRING_VIEW_H