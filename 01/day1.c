#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define DAY 1

int cmp_ints(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

#define LINE_SIZE 1024

int part1(FILE* file)
{
    int *left = NULL;
    int *right = NULL;

    char line[LINE_SIZE];
    char word[LINE_SIZE];
    while (fgets(line, LINE_SIZE, file)) {

        char *ch1 = line;
        int i = 0;
        int num;

        while (!isspace(*ch1)) ch1++; 
        strncpy(word, line, ch1 - line);
        i = atoi(word);
        arrput(left, i);

        while (isspace(*ch1)) ch1++; 

        char *ch2 = ch1;
        while (!isspace(*ch2)) ch2++; 
        strncpy(word, ch1, ch2 - ch1);
        i = atoi(word);
        arrput(right, i);
    }

    qsort(left, arrlen(left), sizeof(int), cmp_ints);
    qsort(right, arrlen(right), sizeof(int), cmp_ints);

    int total = 0;
    for (int i = 0; i < arrlen(left); i++) {
        total += abs(left[i] - right[i]);
    }
    return total;
}

int part2(FILE *file)
{
    int *left = NULL;

    struct {int key; int value;} *right = NULL;
    hmdefault(right, 0);

    char line[LINE_SIZE];
    char word[LINE_SIZE];
    while (fgets(line, LINE_SIZE, file)) {
        char *ch1 = line;
        int i = 0;
        int num;

        while (!isspace(*ch1)) ch1++; 
        strncpy(word, line, ch1 - line);
        i = atoi(word);
        arrput(left, i);

        while (isspace(*ch1)) ch1++; 

        char *ch2 = ch1;
        while (!isspace(*ch2)) ch2++; 
        strncpy(word, ch1, ch2 - ch1);
        i = atoi(word);
        int count = hmget(right, i);
        hmput(right, i, ++count);
    }

    int total = 0;
    for (int i = 0; i < arrlen(left); i++) {
        int v = hmget(right, left[i]);
        total += left[i] * v;
    }
    return total;
}

int main(int argc, char *argv[])
{
    printf("---- Day %d ----\n", DAY);

    FILE *file = stdin;
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 0;
        }
    }

    printf("%d\n", part1(file));
    rewind(file);
    printf("%d\n", part2(file));

    return 0;
}

