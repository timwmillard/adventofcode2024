#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define DAY 3

#define LINE_SIZE 1024

typedef enum {
    INVALID, // Start
    CHAR_M,
    CHAR_U,
    CHAR_L,
    OPEN_BRAKET,
    DIGIT_1,
    COMMA,
    DIGIT_2,
    CLOSE_BRAKET, // End
} State;

#define MAX_DIGITS 20

int part1(FILE* file)
{
    int total = 0;

    char num[MAX_DIGITS];
    int num_count;
    int num1, num2;
    int count = 0; // delete me

    char ch;
    State state = INVALID;
    while ((ch = fgetc(file)) != EOF) {

        State before = state;

        switch (state) {
            case INVALID:
                if (ch == 'm') state = CHAR_M;
                break;
            case CHAR_M:
                if (ch == 'u') state = CHAR_U;
                else state = INVALID;
                break;
            case CHAR_U:
                if (ch == 'l') state = CHAR_L;
                else state = INVALID;
                break;
            case CHAR_L:
                if (ch == '(') state = OPEN_BRAKET;
                else state = INVALID;
                break;
            case OPEN_BRAKET:
                if (isdigit(ch)) {
                    num_count = 0;
                    num[0] = ch;

                    state = DIGIT_1;
                } else state = INVALID;
                break;
            case DIGIT_1:
                if (isdigit(ch)) {
                    num[++num_count] = ch;
                } else if (ch == ',') {
                    num[++num_count] = '\0';
                    num1 = atoi(num);

                    state = COMMA;
                } else state = INVALID;
                break;
            case COMMA:
                if (isdigit(ch)) {
                    num_count = 0;
                    num[0] = ch;

                    state = DIGIT_2;
                } else state = INVALID;
                break;
            case DIGIT_2:
                if (isdigit(ch)) {
                    num[++num_count] = ch;
                } else if (ch == ')') state = CLOSE_BRAKET;
                else state = INVALID;
                break;
            case CLOSE_BRAKET:
                num[++num_count] = '\0';
                num2 = atoi(num);

                // Do Multiply
                total += num1 * num2;

                if (ch == 'm') state = CHAR_M;
                else state = INVALID;
                break;
            default:
                state = INVALID;
        }
    }
    return total;
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

    fclose(file);

    return 0;
}

