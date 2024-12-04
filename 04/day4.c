#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <limits.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define DAY 4

#define LINE_SIZE 1024

typedef struct {
    char *data;
    int rows;
    int cols;
} Grid;

size_t filelen(FILE *f);
bool xmas_north(Grid *grid, int row, int col);
bool xmas_east(Grid *grid, int row, int col);
bool xmas_south(Grid *grid, int row, int col);
bool xmas_west(Grid *grid, int row, int col);
bool xmas_north_east(Grid *grid, int row, int col);
bool xmas_north_west(Grid *grid, int row, int col);
bool xmas_south_east(Grid *grid, int row, int col);
bool xmas_south_west(Grid *grid, int row, int col);

/*
  | 0123456
--+--------
0 | S  S  S
1 |  A A A 
2 |   MMM  
3 | SAMXMAS
4 |   MMM  
5 |  A A A 
6 | S  S  S
*/

int part1(FILE* file)
{
    Grid g;
    char *grid;
    int rows = 0;
    int cols = 0;

    size_t file_len = filelen(file);

    grid = malloc(file_len + 1);

    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, file)) {
        cols = strlen(line);
        // Remove newline
        char *ch = &line[cols-1];
        while (*ch == '\n' || *ch == '\r') {
            ch--;
            cols--;
        }
        ch[cols] = '\0';

        memcpy(grid+rows*cols, line, cols);

        rows++;
    }
    g.rows = rows;
    g.cols = cols;
    g.data = grid;

    // XMAS
    int count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            char cell = grid[r*cols + c]; 
            if (cell == 'X') {
                if (xmas_north(&g, r, c)){ count++; }
                if (xmas_south(&g, r, c)){ count++; }
                if (xmas_west(&g, r, c)){ count++; }
                if (xmas_east(&g, r, c)){ count++; }

                if (xmas_north_west(&g, r, c)){ count++; }
                if (xmas_north_east(&g, r, c)){ count++; }
                if (xmas_south_west(&g, r, c)){ count++; }
                if (xmas_south_east(&g, r, c)){ count++; }
            }
        }
    }
    return count;
}

// -row
bool xmas_north(Grid *g, int r, int c) {
    return (r - 3 >= 0)
        && g->data[(r-1)*g->cols + c] == 'M'
        && g->data[(r-2)*g->cols + c] == 'A'
        && g->data[(r-3)*g->cols + c] == 'S';
}

// +col
bool xmas_east(Grid *g, int r, int c) {
    return (c + 3 < g->cols)
        && g->data[r*g->cols + c+1] == 'M'
        && g->data[r*g->cols + c+2] == 'A'
        && g->data[r*g->cols + c+3] == 'S';
}

// +row
bool xmas_south(Grid *g, int r, int c) {
    return (r + 3 < g->rows)
        && g->data[(r+1)*g->cols + c] == 'M'
        && g->data[(r+2)*g->cols + c] == 'A'
        && g->data[(r+3)*g->cols + c] == 'S';
}

// -col
bool xmas_west(Grid *g, int r, int c) {
    return (c - 3 >= 0)
        && g->data[r*g->cols + c-1] == 'M'
        && g->data[r*g->cols + c-2] == 'A'
        && g->data[r*g->cols + c-3] == 'S';
}

// -row, +col
bool xmas_north_east(Grid *g, int r, int c) {
    return ((r - 3) >= 0 && c + 3 < g->cols)
        && g->data[(r-1)*g->cols + c+1] == 'M'
        && g->data[(r-2)*g->cols + c+2] == 'A'
        && g->data[(r-3)*g->cols + c+3] == 'S';
}

// -row, -col
bool xmas_north_west(Grid *g, int r, int c) {
    return (r - 3 >= 0 && c - 3 >= 0)
        && g->data[(r-1)*g->cols + c-1] == 'M'
        && g->data[(r-2)*g->cols + c-2] == 'A'
        && g->data[(r-3)*g->cols + c-3] == 'S';
}

// +row, +col
bool xmas_south_east(Grid *g, int r, int c) {
    return (r + 3 < g->rows && c + 3 < g->cols)
        && g->data[(r+1)*g->cols + c+1] == 'M'
        && g->data[(r+2)*g->cols + c+2] == 'A'
        && g->data[(r+3)*g->cols + c+3] == 'S';
}

// +row, -col
bool xmas_south_west(Grid *g, int r, int c) {
    return (r + 3 < g->rows && c - 3 >= 0)
        && g->data[(r+1)*g->cols + c-1] == 'M'
        && g->data[(r+2)*g->cols + c-2] == 'A'
        && g->data[(r+3)*g->cols + c-3] == 'S';
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

size_t filelen(FILE *f)
{
   size_t len, pos;
   pos = ftell(f);
   fseek(f, 0, SEEK_END);
   len = ftell(f);
   fseek(f, pos, SEEK_SET);
   return len;
}

