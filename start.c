
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

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

    if (argc > 0)
        opts->input = fopen(argv[0], "r");
    else
        opts->input = stdin;
}

int main(int argc, char *argv[])
{
    struct options opts;
    parse_options(argc, argv, &opts);

    FILE *input = opts.input;


    return 0;
}

