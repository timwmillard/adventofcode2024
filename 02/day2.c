#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define DAY 2

#define LINE_SIZE 1024

int part1(FILE* file)
{
    int safe = 0;
    int *report = NULL; 

    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, file)) {
        char *start = line;
        char *ch = line;

        while (*ch) {
            // skip leading space
            while (*ch && isspace(*ch)) ch++; 

            if (*ch && isdigit(*ch)) {
                int i = atoi(ch);
                arrput(report, i);
                while (*ch && isdigit(*ch)) ch++; 
            } 
        }

        if (arrlen(report) < 2) goto next_report;

        bool inc = (report[1] - report[0]) < 0;
        for (int i = 0, j=1; j < arrlen(report); i++, j++) {
            int diff = report[j] - report[i];

            if ( diff == 0) goto next_report;
            if (inc && diff > 0) goto next_report;
            if (!inc && diff < 0) goto next_report;
            diff = abs(diff);
            if (diff > 3) goto next_report;

        }
        safe++;

    next_report:
        arrfree(report);
        report = NULL;
    }

    return safe;
}

int part2(FILE *file)
{
    return 0;
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

