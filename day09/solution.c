#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

int char_to_digit(char c);

int a[ROW][COL] = {0};


int main(void)
{
    FILE *fp = fopen(FILENAME, "r");

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

    fclose(fp);
    return 0;
}


int char_to_digit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else
        assert(0 && "char is not digit");
}
