#include <stdio.h>
#include "types.h"

int say1(char* prefix) {
    return printf("%s hello1\n", prefix);
}

int say2(char* prefix) {
    return printf("%s hello2\n", prefix);
}

Function functions[] = {
        {
                .name = "say1",
                .func = say1
        },
        {
                .name = "say2",
                .func = say2
        }
};
int functions_count = sizeof(functions) / sizeof(Function);