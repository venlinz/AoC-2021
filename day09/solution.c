#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>

/* #define SAMPLE */
#ifdef SAMPLE
#define FILENAME "sample.txt"
#define ROW 5
#define COL 10
#else
#define FILENAME "input.txt"
#define ROW 100
#define COL 100
#endif

#define DIRS_CAP 4

size_t DIRS[DIRS_CAP][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};


void part1(void);
void part1_elegant(void);
void populate_data(void);
bool islow(const size_t x, const size_t y);


int char_to_digit(char c);
int a[ROW][COL] = {0};
int v[ROW][COL] = {0};


int main(void)
{
    populate_data();
    part1_elegant();
    return 0;
}


void part1_elegant()
{
    size_t count = 0;
    for (size_t x = 0; x < ROW; x++)
    {
        for (size_t y = 0; y < COL; y++)
        {
            count += islow(x, y) ? a[x][y] + 1 : 0;
        }
    }
    printf("count: %lu\n", count);
}


bool islow(const size_t x, const size_t y)
{
    for (size_t i = 0; i < DIRS_CAP; i++)
    {
        int newX = x + DIRS[i][0];
        int newY = y + DIRS[i][1];
        if (newX <= -1 || newX > ROW - 1)
            continue;
        if (newY <= -1 || newY > COL - 1)
            continue;
        if (a[x][y] >= a[newX][newY])
        {
            return false;
        }
    }
    return true;
}


void populate_data(void)
{
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        fprintf(stderr, "Could not open the file %s: %s\n", FILENAME
                , strerror(errno));
        exit(1);
    }

    size_t limit = COL + 2;
    char *lineptr = malloc(limit);
    size_t row = 0;
    size_t col = 0;
    while (getline(&lineptr, &limit, fp) > 0)
    {
        for (size_t i = 0; i < COL; i++)
            a[row][col++] = char_to_digit(lineptr[i]);
        col = 0;
        row++;
    }
    free(lineptr);
    fclose(fp);
}


void part1(void)
{
    size_t sum = 0;
    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < COL; j++)
        {
            if (i == 0) {
                if (j == 0) {
                    if (a[i][j + 1] > a[i][j] 
                            && a[i + 1][j] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
                else if (j == COL - 1) {
                    if (a[i][j - 1] > a[i][j] 
                            && a[i + 1][j] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
                else {
                    if (a[i][j - 1] > a[i][j] 
                            && a[i][j + 1] > a[i][j] 
                            && a[i + 1][j] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
            }
            else if (i == ROW - 1) {
                if (j == 0) {
                    if (a[i - 1][j] > a[i][j]
                            && a[i][j + 1] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
                else if (j == COL - 1) {
                    if (a[i][j - 1] > a[i][j]
                            && a[i - 1][j] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
                else {
                    if (a[i][j - 1] > a[i][j]
                            && a[i][j + 1] > a[i][j]
                            && a[i - 1][j] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
            }
            else {
                if (j == 0) {
                    if (a[i - 1][j] > a[i][j]
                            && a[i + 1][j] > a[i][j]
                            && a[i][j + 1] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
                else if (j == COL - 1) {
                    if (a[i - 1][j] > a[i][j]
                            && a[i + 1][j] > a[i][j]
                            && a[i][j - 1] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
                else {
                    if (a[i][j - 1] > a[i][j]
                            && a[i][j + 1] > a[i][j]
                            && a[i - 1][j] > a[i][j]
                            && a[i + 1][j] > a[i][j]) {
                        sum += a[i][j] + 1;
                    }
                }
            }
        }
    }
    printf("ans: %lu\n", sum);
}


int char_to_digit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else
        assert(0 && "char is not digit");
}
