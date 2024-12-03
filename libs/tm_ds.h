/*
    Utilites for the stb_ds.h code.
*/

#include <stdio.h>
#include "stb_ds.h"

int *arrcopy(int *src)
{
    int *dst = NULL;
    for (int i = 0; i < arrlen(src); i++) {
        arrput(dst, src[i]);
    }
    return dst;
}

void arrprint(char *msg, int *arr)
{
    printf("%s", msg);
    for (int i = 0; i < arrlen(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
