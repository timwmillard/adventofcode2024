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

typedef enum {
    UNKNOWN = 0,
    INCREASING = 1,
    DECREASING = 2,
    STOP = 3
} Direction;

Direction direction(int diff)
{
    Direction dir;
    if (diff < 0) dir = DECREASING;
    else if (diff > 0) dir = INCREASING;
    else dir = STOP;
    return dir;
}

bool check_safe(Direction report_dir, int diff)
{
    Direction dir = direction(diff);

    if (dir == STOP) return false;
    if (report_dir == INCREASING && dir == DECREASING) return false;
    if (report_dir == DECREASING && dir == INCREASING) return false;
    if (abs(diff) > 3) return false;

    return true;
}

bool check_report(int *report)
{
    Direction report_dir = UNKNOWN;
    for (int i = 0, j=1; j < arrlen(report); i++, j++) {
        int diff = report[i] - report[j];
        Direction dir = direction(report[i] - report[j]);
        if (i == 0) report_dir = dir;

        if (!check_safe(report_dir, diff)) return false;
    }
    return true;
}

int *arr_copy(int *src)
{
    int *dst = NULL;
    for (int i = 0; i < arrlen(src); i++) {
        arrput(dst, src[i]);
    }
    return dst;
}

void arr_print(char *msg, int *arr)
{
    printf("%s", msg);
    for (int i = 0; i < arrlen(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int part2(FILE *file)
{
    int safe = 0;
    int *report = NULL; 

    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, file)) {
        char *start = line;
        char *ch = line;

        while (*ch) {
            // skip leadi space
            while (*ch && isspace(*ch)) ch++; 

            if (*ch && isdigit(*ch)) {
                int i = atoi(ch);
                arrput(report, i);
                while (*ch && isdigit(*ch)) ch++; 
            } 
        }

        if (arrlen(report) < 2) goto next_report;

        if (!check_report(report)) {
            for (int i = 0; i < arrlen(report); i++) {
                int *new = arr_copy(report);
                arrdel(new, i);
                if (check_report(new)) {
                    safe++;
                    goto next_report;
                }
                arrfree(new);
                new = NULL;
            }
            goto next_report;
        }
        safe++;

    next_report:
        arrfree(report);
        report = NULL;
    }

    return safe;

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

