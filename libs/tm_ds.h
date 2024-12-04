/*
    Utilites for the stb_ds.h code.
*/

#include <stdio.h>

#ifndef INCLUDE_STB_DS_H
#include "stb_ds.h"
#endif

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

size_t filelen(FILE *f)
{
   size_t len, pos;
   pos = ftell(f);
   fseek(f, 0, SEEK_END);
   len = ftell(f);
   fseek(f, pos, SEEK_SET);
   return len;
}

char **stringfile(char *filename, int *plen)
{
   FILE *f = fopen(filename, "rb");
   char *buffer, **list=NULL, *s;
   size_t len, count, i;

   if (!f) return NULL;
   len = filelen(f);
   buffer = (char *) malloc(len+1);
   len = fread(buffer, 1, len, f);
   buffer[len] = 0;
   fclose(f);

   // two passes through: first time count lines, second time set them
   for (i=0; i < 2; ++i) {
      s = buffer;
      if (i == 1)
         list[0] = s;
      count = 1;
      while (*s) {
         if (*s == '\n' || *s == '\r') {
            // detect if both cr & lf are together
            int crlf = (s[0] + s[1]) == ('\n' + '\r');
            if (i == 1) *s = 0;
            if (crlf) ++s;
            if (s[1]) {  // it's not over yet
               if (i == 1) list[count] = s+1;
               ++count;
            }
         }
         ++s;
      }
      if (i == 0) {
         list = (char **) malloc(sizeof(*list) * (count+1) + len+1);
         if (!list) return NULL;
         list[count] = 0;
         // recopy the file so there's just a single allocation to free
         memcpy(&list[count+1], buffer, len+1);
         free(buffer);
         buffer = (char *) &list[count+1];
         if (plen) *plen = count;
      }
   }
   return list;
}

