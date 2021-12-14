#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* #define SAMPLE */
#ifndef SAMPLE
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif


#define MAX_LEN 1024
int random_order_array[MAX_LEN];
size_t roa_size = 0;

#define ROW_LEN 5
#define COL_LEN ROW_LEN
#define MAX_BOARDS_COUNT 150

typedef int matrix2d[ROW_LEN][COL_LEN];
typedef struct {
    matrix2d num_board;
} game_board;

size_t boards_count = 0;
game_board game_boards[MAX_BOARDS_COUNT];

typedef struct {
    int board_idx;
    int winning_draw;
} winning_entry;

void fill_board();
void get_roa();
void get_data();
winning_entry check_won_board();

void print_i32array(int *arr, size_t len);
void print_2d_i32array(int *arr_2d, size_t d_m, size_t d_n);

// I don't need these two functions because I have to preserve order.
void ins_sort_asc(int *a, int len);
bool contains(int *a, int len, int elem); // using binary search

int main(void)
{
    get_data();
    winning_entry ent = check_won_board();
    if (ent.board_idx == -1)
    {
        printf("winner not found\n");
    }
    else
    {
        printf("found\n");
        printf("board_idx: %d\n",    ent.board_idx);
        int *board = (int *)game_boards[ent.board_idx].num_board;
        print_2d_i32array(board, ROW_LEN, COL_LEN);
        printf("winning_draw: %d\n", ent.winning_draw);
        size_t sum_of_unmarked = 0;
        for (size_t r = 0; r < ROW_LEN; r++)
        {
            for (size_t c = 0; c < COL_LEN; c++)
            {
                if (game_boards[ent.board_idx].num_board[r][c] != -1)
                    sum_of_unmarked += game_boards[ent.board_idx].num_board[r][c];
            }
        }
        printf("sum_of_unmarked: %lu\n", sum_of_unmarked);
        printf("answer: %lu\n", sum_of_unmarked * ent.winning_draw);
    }
    printf("Here come the table\n");
    return 0;
}


winning_entry check_won_board()
{
    winning_entry ent = {0};
    for (size_t r_idx = 0; r_idx < roa_size; r_idx++)
    {
        int rand_num = random_order_array[r_idx];
        for (size_t board = 0; board < boards_count; board++)
        {
            for (size_t r = 0; r < ROW_LEN; r++)
            {
                for (size_t c = 0; c < COL_LEN; c++)
                {
                    if (rand_num == game_boards[board].num_board[r][c])
                    {
                        game_boards[board].num_board[r][c] = -1;
                        int cur_col_res = -1;
                        int cur_row_res = -1;
                        // I can modify this loop to iterate through 
                        // non square matrices.
                        // need to add iteration if col is longer than row
                        // or need to remove iteration if col is shorter than row.
                        /* for (size_t cur_row_idx = 0, cur_col_idx = 0; */
                        /*         cur_row_idx < ROW_LEN; */
                        /*         cur_row_idx++, cur_col_idx++) */
                        for (size_t col_row_idx = 0;
                                col_row_idx < ROW_LEN;
                                col_row_idx++)
                        {
                            if (game_boards[board].num_board[col_row_idx][c] != -1)
                            {
                                cur_col_res = 1;
                            }
                            if (game_boards[board].num_board[r][col_row_idx] != -1)
                            {
                                cur_row_res = 1;
                            }
                        }
                        if (cur_col_res == -1 || cur_row_res == -1)
                        {
                            ent = (winning_entry) { .board_idx = board,
                                .winning_draw = rand_num };
                            return ent;
                        }
                    }
                }
            }
        }
    }
    ent = (winning_entry) { .board_idx = -1, .winning_draw = -1 };
    return ent;
}


void fill_board(FILE *fp)
{
    boards_count = 0;
    memset(game_boards, 0, MAX_BOARDS_COUNT * sizeof(game_board));
    size_t limit = 100;
    char *linep = malloc(limit);
    char *begin = linep;
    while (getline(&linep, &limit, fp) > 0)
    {
        if (strlen(linep) == 1)
            continue;
        for (size_t row = 0; row < ROW_LEN; ++row)
        {
            errno = 0;
            size_t line_len = strlen(linep);
            if (line_len > 1)
            {
                char *tok = strtok(linep, " ");
                long int num = 0;
                for (size_t col = 0; (tok != NULL); ++col)
                {
                    errno = 0;
                    num = strtol(tok , NULL, 10);
                    /* printf("num: %ld\n", num); */
                    if (errno != 0)
                    {
                        perror("strtol");
                        exit(EXIT_FAILURE);
                    }
                    game_boards[boards_count].num_board[row][col] = num;
                    tok = strtok(NULL, " ");
                }
                getline(&linep, &limit, fp);
            }
            else if (line_len == 1)
            {
                if (getline(&linep, &limit, fp) > 0)
                {
                    row--;
                    continue;
                }
                if (errno != 0)
                {
                    perror("getline");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                fprintf(stderr, "end\n");
            }
            if (errno != 0)
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }
        boards_count++;
        if (boards_count >= MAX_BOARDS_COUNT)
        {
            fprintf(stderr, "less no. of boards available\n");
            exit(EXIT_FAILURE);
        }
    }
    free(begin);
}

void get_roa(FILE *fp)
{
    char *linep = malloc(MAX_LEN);
    if (linep == NULL)
    {
        perror("line: malloc");
        exit(EXIT_FAILURE);
    }

    size_t limit = MAX_LEN;
    int ret = getline(&linep, &limit, fp);
    if (ret < 0)
    {
        perror("getline");
        exit(EXIT_FAILURE);
    }

    char *begin = linep;
    char *tok = strtok(linep, ",");
    long int num = 0;
    while (tok != NULL)
    {
        num = strtol(tok , NULL, 10);
        if (errno != 0)
        {
            perror("strtol");
            exit(EXIT_FAILURE);
        }
        random_order_array[roa_size++] = (int) num;
        tok = strtok(NULL, ",");
    }
    free(begin);

    linep = malloc(100);
    if (linep == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    free(linep);
}


void get_data()
{
    FILE *fp = fopen(FILENAME, "r");
    errno = 0;
    if (fp == NULL)
    {
        perror("fopen: ");
        exit(EXIT_FAILURE);
    }
    get_roa(fp);
    print_i32array(random_order_array, roa_size);
    fill_board(fp);
    fclose(fp);
}


void print_i32array(int *arr, size_t len)
{
    if (len <= (unsigned long) 0)
    {
        fprintf(stderr, "Invalid argument length");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; i++)
    {
        printf("%5d ", arr[i]);
    }
    printf("\n");
}


void print_2d_i32array(int *arr_2d, size_t d_m, size_t d_n)
{
    if (d_m <= 0 || d_n <= 0)
    {
        fprintf(stderr, "Invalid argument(s) dimensions\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < d_m; ++i)
    {
        print_i32array((arr_2d + (i * d_m)), d_n);
    }
}

void ins_sort_asc(int *a, int len)
{
    if (len <= 0)
    {
        fprintf(stderr, "invalid argument len\n");
        exit(EXIT_FAILURE);
    }
    int t = 0;
    size_t iters = 0;
    for (int i = 1; i < len; ++i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            iters++;
            if (a[j] > a[i])
            {
                t = a[j];
                a[j] = a[i];
                a[i] = t;
                i--;
            }
            else
            {
                break;
            }
        }
    }
    printf("insertion_sort: iters = %lu\n", iters);
}


bool contains(int *a, int len, int elem) // using binary search
{
    size_t iters = 0;
    
    if (elem > a[len - 1])
        return false;
    else if (elem < a[0])
        return false;
    else if (elem == a[0])
        return true;
    else if (elem == a[len - 1])
        return true;

    int start = 0;
    int end = len;
    int mid = (0 + end) / 2;
    while (start <= end)
    {
        iters++;
        mid = (start + end) / 2;
        if (elem > a[mid])
            start = mid + 1;
        else if (elem < a[mid])
            end = mid - 1;
        else
        {
            printf("bin_search: iters = %lu\n", iters);
            return true;
        }
    }
    printf("bin_search: iters = %lu\n", iters);
    return false;
}
