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
    printf("Avent of Code 2024 - Day %d part 2\n", DAY);
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

    if (argc > 0)
        opts->input = fopen(argv[0], "r");
    else
        opts->input = stdin;
}

#define LINE_SIZE 1024

int main(int argc, char *argv[])
{
    struct options opts;
    parse_options(argc, argv, &opts);

    FILE *file = opts.input;

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
    printf("%d\n", total);

    return 0;
}

