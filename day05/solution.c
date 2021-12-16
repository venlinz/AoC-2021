#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define SAMPLE
#ifndef SAMPLE
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define RANGE 1000


typedef struct {
    int x, y;
} point_t;

void print_point_t(point_t pt);
void set_lines(int **sea_floor, point_t s, point_t e);


int main(void)
{
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char *line = malloc(25);
    if (line == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    size_t limit = 25;
    int sea_floor[RANGE][RANGE] = {0};
    (void) sea_floor;
    while ((getline(&line, &limit, fp) > 0))
    {
        char *delim = ",-> ";
        char *tok = strtok(line, delim);
        int cur_cordinates_arr[4];
        for (int cord_idx = 0; tok != NULL; cord_idx++)
        {
            errno = 0;  // no need to set this to zero,
                        //because I will exit at first error.
            long num = strtol(tok, NULL, 10);
            tok = strtok(NULL, delim);
            if (errno != 0)
            {
                perror("strtol");
                exit(EXIT_FAILURE);
            }
            cur_cordinates_arr[cord_idx] = (int) num;
        }
        point_t line_start = { .x = cur_cordinates_arr[0], .y = cur_cordinates_arr[1] };
        (void) line_start;
        /* print_point_t(line_start); */
        point_t line_end = { .x = cur_cordinates_arr[2], .y = cur_cordinates_arr[3] };
        /* print_point_t(line_end); */
        (void) line_end;
        set_lines((int **)sea_floor, line_start, line_end);
    }
    free(line);
    (void) sea_floor;
    return 0;
}

void set_lines(int **sea_floor, point_t s, point_t e)
{
    // vertical line
    int line_len = 0;
    if (s.x == e.x)
    {
        line_len = abs(s.y - e.y);
    }

    // Horizontal line.
    (void) sea_floor;
    if (s.y == e.y)
    {
        line_len = abs(s.x - e.x);
    }
    printf("line_len: %d\n", line_len);
}

void print_point_t(point_t pt)
{
    printf("x: %d, y: %d\n", pt.x, pt.y);
}
