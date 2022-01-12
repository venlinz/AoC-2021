#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

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
#define LEN 250

size_t DIRS[DIRS_CAP][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};


void part1(void);
void part2(void);
size_t crawl(size_t x, size_t y);
void part1_elegant(void);
void populate_data(void);
bool islow(const size_t x, const size_t y);
void ins_sort(size_t a[], size_t len);
void swap(size_t *a, size_t *b);


int char_to_digit(char c);
int a[ROW][COL] = {0};
int v[ROW][COL] = {0};


int main(void)
{

    populate_data();
    part1_elegant();
    /* part1(); */
    part2();
    return 0;
}

void swap(size_t *a, size_t *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void ins_sort(size_t *a, size_t len)
{
    for (size_t i = 1; i < len; i++)
    {
        int idx = i;
        for (int j = i - 1; j >= 0; j--)
        {
            if (a[j] > a[idx])
            {
                swap(&a[j], &a[idx]);
                idx--;
            }
            else
                break;
        }
    }
}

void part2(void)
{
    size_t counts[LEN] = {0};
    size_t idx = 0;

    for (size_t x = 0; x < ROW; x++)
    {
        for (size_t y = 0; y < COL; y++)
        {
            if (a[x][y] != 9)
            {
                size_t res = crawl(x, y);
                counts[idx++] = res - 1;
            }
        }
    }
    ins_sort(counts, idx);
    size_t m1 = counts[idx - 1];
    size_t m2 = counts[idx - 2];
    size_t m3 = counts[idx - 3];
    printf("part2 answer: %lu\n", m1 * m2 * m3);
}


size_t crawl(size_t x, size_t y)
{
    size_t res = 1;
    for (size_t i = 0; i < DIRS_CAP; i++)
    {
        int newX = x + DIRS[i][0];
        int newY = y + DIRS[i][1];
        if (newX <= -1 || newX > ROW - 1)
            continue;
        if (newY <= -1 || newY > COL - 1)
            continue;

        if (a[newX][newY] == 9)
        {
            continue;
        }
        else
        {
            a[newX][newY] = 9;
            res += crawl(newX, newY);
        }
    }

    return res;
}


// Thanks to tsoding
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
    printf("part1 answer: %lu\n", count);
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
    printf("part1 answer: %lu\n", sum);
}


int char_to_digit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else
        assert(0 && "char is not digit");
}
