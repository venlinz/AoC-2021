#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

/* #define SAMPLE */
#ifndef SAMPLE
#define FILENAME "input.txt"
#define RANGE 1000 //not for number of line but for max cord-value
#else
#define FILENAME "sample.txt"
#define RANGE 10
#endif


typedef struct {
    int x, y;
} point_t;

typedef struct {
    int8_t mat[RANGE][RANGE];
} matrix;

void print_point_t(point_t pt);
void set_lines(matrix *sea_floor,
        point_t s,
        point_t e);


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
    
    matrix *sea_floor = malloc(sizeof(matrix));
    memset(sea_floor, 0, sizeof(matrix));
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
        point_t line_end = { .x = cur_cordinates_arr[2], .y = cur_cordinates_arr[3] };
        set_lines(sea_floor, line_start, line_end);
    }
    size_t danger_zones = 0;
    for (int i = 0; i < RANGE; ++i)
    {
        for (int j = 0; j < RANGE; ++j)
        {
            if (sea_floor->mat[i][j] > 1)
                danger_zones++;
#ifdef SAMPLE
            printf("%d", sea_floor->mat[i][j]);
#endif
        }
#ifdef SAMPLE
        printf("\n");
#endif
    }
    printf("danger_zones: %lu\n", danger_zones);
    free(line);
    fclose(fp);
    return 0;
}


void set_lines(matrix *sea_floor,
        point_t s,
        point_t e)
{
    int line_len = 0;
    if (s.x == e.x)  // vertical line
    {
        line_len = (e.y - s.y);
        int y_diff = 1;
        if (line_len < 0)
        {
            y_diff = -1;
            line_len = -line_len;
        }
        int cur_y = s.y;
        for (int i = 0; i <= line_len; ++i, cur_y += y_diff)
        {
            /* sea_floor->mat[row][col]++; */
            sea_floor->mat[cur_y][s.x]++;
        }
    }
    else if (s.y == e.y) // Horizontal line.
    {
        line_len = (e.x - s.x);
        int x_diff = 1;
        if (line_len < 0)
        {
            x_diff = -1;
            line_len = -line_len;
        }
        int cur_x = s.x;
        for (int i = 0; i <= line_len; ++i, cur_x += x_diff)
        {
            /* sea_floor->mat[row][col]++; */
            sea_floor->mat[s.y][cur_x]++;
        }
    }
    else // diagonol
    {
        int line_len_x = (e.x - s.x);
        int line_len_y = (e.y - s.y);
        if (abs(line_len_x) != abs(line_len_y))
        {
            return;
        }

        int x_diff = 1;
        int y_diff = 1;
        if (line_len_x < 0)
        {
            x_diff = -1;
        }
        if (line_len_y < 0)
        {
            y_diff = -1;
        }
        line_len = abs(line_len_x);

        int cur_x = s.x;
        int cur_y = s.y;
        for (int i = 0;
                i <= line_len;
                ++i, 
                cur_x += x_diff,
                cur_y += y_diff)
        {
            /* sea_floor->mat[row][col]++; */
            sea_floor->mat[cur_y][cur_x]++;
        }
    }
}


void print_point_t(point_t pt)
{
    printf("x: %d, y: %d\n", pt.x, pt.y);
}
