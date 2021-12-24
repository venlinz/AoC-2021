#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


/* #define SAMPLE */
#ifdef SAMPLE
#define FILENAME "sample.txt"
#define LIMIT 10
#else
#define FILENAME "input.txt"
#define LIMIT 1000
#endif

#define DELI ","

int sum_of_n(int n)
{
    return (n *(n + 1)) / 2;
}

int main(void)
{
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }


    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    char *input_str = malloc(file_size);
    if (!input_str)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *ret = fgets(input_str, file_size, fp);
    if (!ret)
    {
        errno = EFAULT;
        perror("fgets");
        exit(EXIT_FAILURE);
    }
    /* printf("out: %s", ret); */

    int input_int[LIMIT] = {0};
    char *tok = strtok(input_str, DELI);
    /* printf("tokenizing\n"); */
    long num = 0;
    size_t idx = 0;
    size_t max_num = 0;
    while (tok != NULL)
    {
        num = strtol(tok, NULL, 10);
        if ((long int) max_num < num)
            max_num = num;

        errno = 0;
        if (errno != 0)
        {
            perror("strtol");
            exit(EXIT_FAILURE);
        }
        input_int[idx++] = num;
        tok = strtok(NULL, DELI);
    }

    int input_elem_count[max_num + 1];
    for (size_t i = 0; i < max_num + 1; i++)
        input_elem_count[i] = 0;

    for (size_t i = 0, j = 0; i < max_num + 1 && j < idx; i++, j++)
        input_elem_count[input_int[j]]++;

    size_t smallest_cost = 1000000000;
    for (size_t move_position = 0;
            move_position < max_num + 1;
            move_position++)
    {
        size_t fuel_cost = 0;
        for (size_t i = 0; i < idx; i++)
        {
            int ft = input_int[i] - move_position;
            if (ft < 0)
                ft = -ft;
            fuel_cost += ft;
        }
        if (fuel_cost < smallest_cost)
            smallest_cost = fuel_cost;
    }
    printf("part1: %lu\n", smallest_cost);

    smallest_cost = 1000000000;
    for (size_t move_position = 0;
            move_position < max_num + 1;
            move_position++)
    {
        size_t fuel_cost = 0;
        for (size_t i = 0; i < idx; i++)
        {
            int ft = input_int[i] - move_position  - 1;
            if (ft < 0)
                ft = -ft;
            fuel_cost += sum_of_n(ft);
        }
        if (fuel_cost < smallest_cost)
            smallest_cost = fuel_cost;
    }
    printf("part2: %lu\n", smallest_cost);

    free(input_str);
    fclose(fp);
    return 0;
}
