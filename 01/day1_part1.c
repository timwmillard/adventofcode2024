#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define DAY 1

static void version(void)
{
    printf("Avent of Code 2024 - Day %d\n", DAY);
}

void usage()
{
    printf("day%d run advent of code problem\n\n", DAY);
    printf("Usage:\n");
    printf("  day%d [OPTION]... FILE\n", DAY);

    printf("\nOptions:\n");
    printf("  -h, --help                        show this help, then exit\n");
    printf("  -v, --version                     output version information\n");
}

struct options {
    FILE *input;
};

static void parse_options(int argc, char *argv[], struct options *opts) 
{
    /* options descriptor */
    static struct option longopts[] = {
        { "help",        no_argument,       NULL, 'h' },
        { "version",     no_argument,       NULL, 'v' },
        { NULL,          0,                 NULL,  0  }
    };

    int ch;
    while ((ch = getopt_long(argc, argv, "hv", longopts, NULL)) != -1) {
        switch (ch) {
            case 'v':
                version();
                exit(0);
            case 'h':
                usage();
                exit(0);
                // no break, fallthrough to default
            default:
                fprintf(stderr, "Try: day%d --help\n", DAY);
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;

    if (argc > 0) {
        opts->input = fopen(argv[0], "r");
        if (opts->input == NULL) {
            fprintf(stderr, "Error opening file %s\n", argv[0]);
            exit(0);
        }
    } else
        opts->input = stdin;
}

int cmp_ints(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

#define LINE_SIZE 1024

int main(int argc, char *argv[])
{
    struct options opts;
    parse_options(argc, argv, &opts);

    FILE *file = opts.input;

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
    printf("%d\n", total);

    return 0;
}

