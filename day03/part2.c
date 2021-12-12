#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef SAMPLE
#define BITS_COUNT 12
#define FILENAME "input.txt"
#else
#define BITS_COUNT 5
#define FILENAME "sample.txt"
#endif


#define MAX_ARRAY_SIZE 1024
#define MOST true
#define LEAST false

int diagnostic_rep_nums[MAX_ARRAY_SIZE];
int oxy_array[MAX_ARRAY_SIZE] = {0};
int co2_array[MAX_ARRAY_SIZE] = {0};

int find_common_bit(int *diagnostic_rep_nums, size_t size, size_t position, bool most);
int find_least_common_bit(int mcb);


int main(void)
{
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "unable to openfile\n");
        return 1;
    }

    size_t limit = 14;
    char *line = malloc(limit);
    long int num = 0;
    int base = 2;
    size_t rep_nums_count = 0;
    while (getline(&line, &limit, fp) > 0)
    {
        num = strtol(line, NULL, base);
        diagnostic_rep_nums[rep_nums_count] = num;
        rep_nums_count++;
    }
    free(line);
    fclose(fp);

    int bit = 0;
    size_t oxygen_size = 0;
    size_t co2_size = 0;
    size_t position = 0;
    int mcb = find_common_bit(diagnostic_rep_nums, rep_nums_count, position, MOST);
    int shift_len = (BITS_COUNT - position - 1);
    for (size_t i = 0; i < rep_nums_count; ++i)
    {
        bit = (diagnostic_rep_nums[i] >> shift_len) & 1;
        if ((bit & 1) == mcb)
            oxy_array[oxygen_size++] = diagnostic_rep_nums[i];
        else
            co2_array[co2_size++] = diagnostic_rep_nums[i];
    }

    size_t temp_oxygen_size = oxygen_size;
    size_t temp_co2_size = co2_size;
    int lcb = 0;
filter_again:
    for (size_t position = 1; position < BITS_COUNT; ++position)
    {
        mcb = find_common_bit(oxy_array, oxygen_size, position, MOST);
        lcb = find_common_bit(co2_array, co2_size, position, LEAST);
        shift_len = (BITS_COUNT - position - 1);
        for (size_t i = 0; i < oxygen_size; ++i)
        {
            if (oxy_array[i] == -1)
                continue;
            bit = (oxy_array[i] >> shift_len) & 1;
            if (bit != mcb && temp_oxygen_size > 1)
            {
                temp_oxygen_size--;
                oxy_array[i] = -1;
            }
        }

        for (size_t i = 0; i < co2_size; ++i)
        {
            if (co2_array[i] == -1)
                continue;
            bit = (co2_array[i] >> shift_len) & 1;
            if (bit != lcb && temp_co2_size > 1)
            {
                temp_co2_size--;
                co2_array[i] = -1;
            }
        }
    }

    int co2 = 0;
    int oxygen = 0;
    bool set = false;
    if (temp_oxygen_size > 1 || temp_co2_size > 1)
        goto filter_again;
    for (size_t i = 0; i < oxygen_size; ++i)
    {
        if (set && oxy_array[i] != -1)
            printf("ERROR %d\n", oxy_array[i]);
        if (oxy_array[i] != -1)
        {
            set = true;
            oxygen = oxy_array[i];
        }
    }

    set = false;
    for (size_t i = 0; i < co2_size; ++i)
    {
        if (set && co2_array[i] != -1)
            printf("ERROR %d\n", co2_array[i]);
        if (co2_array[i] != -1)
        {
            set = true;
            co2 = co2_array[i];
        }
    }

    printf("oxy: %d co2: %d\n", oxygen, co2);
    printf("ans: %d\n", oxygen * co2);
}


int find_common_bit(int *diagnostic_rep_nums, size_t size, size_t position, bool most)
{
    position += 1;
    if (size == 0)
    {
        return -1;
    }
    if (position > BITS_COUNT)
    {
        return -1;
    }
    int bit = 0;
    int shift_len = (BITS_COUNT - position);
    /* printf("shift_len: %d\n", shift_len); */
    int mcb = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (diagnostic_rep_nums[i] == -1)
            continue;
        bit = (diagnostic_rep_nums[i] >> shift_len) & 1;
        if (bit & 1)
            mcb++;
        else
            mcb--;
    }
    /* printf("\n"); */

    if (!most)
        return find_least_common_bit(mcb);
    if (mcb >= 0)
        return 1;
    return 0;
}


int find_least_common_bit(int mcb)
{
    if (mcb == 0)
        return 0;
    if (mcb > 0)
        return 0;
    return 1;
}
