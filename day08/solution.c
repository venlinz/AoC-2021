/* acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/resource.h>
#include <time.h>

/* #define SAMPLE */
#ifndef SAMPLE
#define FILENAME "input.txt"
#else
#define FILENAME "sample.txt"
#endif

#define SUM_A_TO_G 700

char * stripspace(char *str);
char select_non_match_char(char *str, char *magnet);
char * find_output_value(char *digits);
void part1();
void part2();
double calculate(const struct rusage *b, const struct rusage *a);


int main(void)
{
    /* part1(); */
    clock_t start = clock();
    part2();
    clock_t end = clock();
    long double time_taken = (float)(end - start) / CLOCKS_PER_SEC;
    printf("time taken: %Lf\n", time_taken);
    return 0;
}


void part2(void)
{
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        fprintf(stderr, "Unable to open file %s\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    size_t count_of_digits = 0;
    (void) count_of_digits;

    size_t limit = 150;
    char *lineptr = malloc(limit);
    if (!lineptr)
    {
        fprintf(stderr, "malloc\n");
        exit(EXIT_FAILURE);
    }

    char digits[10][8] = {0};
    int count = 0;
    long sum = 0;
    while ((getline(&lineptr, &limit, fp) > 0))
    {
        char *line_cpy = strdup(lineptr);
        char *sig_pats = strtok(lineptr, "|");
        char *pat = strtok(sig_pats, " ");
        for (size_t idx = 0; pat; idx++)
        {
            strcpy(digits[idx], pat);
            pat = strtok(NULL, " ");
        }
        count++;
        char * segment_code = find_output_value((char *)digits);
        strtok(line_cpy, "|");
        char *outputs = strtok(NULL, "|");
        char *output = strtok(outputs, " ");
        char val_str[5] = {0};
        size_t idx = 0;
        while (output)
        {
            size_t output_len = strlen(stripspace(output));
            /* printf("len: %lu\n", output_len); */
            switch(output_len)
            {
                case 2: 
                    val_str[idx] = '1';
                    break;
                case 3: 
                    val_str[idx] = '7';
                    break;
                case 4: 
                    val_str[idx] = '4';
                    break;
                case 7:
                    val_str[idx] = '8';
                    break;
                case 5:
                    {
                        bool ssr_2 = (bool) strchr(output, segment_code[2]) 
                            & (bool) strchr(output, segment_code[4]); 
                        if (ssr_2)
                        {
                            val_str[idx] = '2';
                            break;
                        }
                        bool ssr_3 = (bool) strchr(output, segment_code[2]) 
                            & (bool) strchr(output, segment_code[5]); 
                        if (ssr_3)
                        {
                            val_str[idx] = '3';
                            break;
                        }
                        val_str[idx] = '5';
                        break;
                    }
                case 6:
                    {
                        // ssr 0
                        if (!strchr(output, segment_code[3]))
                        {
                            val_str[idx] = '0';
                            break;
                        }
                        // ssr 6
                        if (!strchr(output, segment_code[2]))
                        {
                            val_str[idx] = '6';
                            break;
                        }
                        // ssr 9
                        val_str[idx] = '9';
                        break;
                    }
            }
            idx++;
            output = strtok(NULL, " ");
        }
        /* printf("val_str: %s\n", val_str); */
        sum += atoi(val_str);

        /* printf("tok: %s\n", tok); */
        free(segment_code);
        free(line_cpy);
    }
    printf("part2: %ld\n", sum);

    free(lineptr);
    fclose(fp);
}


// parse this input tommorow
char * find_output_value(char *str_stream)
{
    char one[3] = "";
    char four[5] = "";
    char six[7] = "";
    char seven[4] = "";
    (void) four;
    for (int i = 0; i < 10; i++)
    {
        char *digit = (char *)(str_stream + 8 * i);
        size_t digit_i_len = strlen(digit);
        if (digit_i_len == 2)
            strcpy(one, digit);
        else if (digit_i_len == 3)
            strcpy(seven, digit);
        else if (digit_i_len == 4)
            strcpy(four, digit);
    }
    /* printf("one: %s\n", one); */
    /* printf("four: %s\n", four); */
    /* printf("seven: %s\n", seven); */
    char *segments = malloc(8);
    memset(segments, ' ', 8);
    segments[7] = '\0';
    segments[0] = select_non_match_char(seven, one);

    char *four_minus_one = malloc(5);
    memset(four_minus_one, 0, 5);
    char *delim = one;
    char *four_cpy = strdup(four);
    char *tok = strtok(four_cpy, delim);
    while (tok)
    {
        four_minus_one = strcat(four_minus_one, tok);
        tok = strtok(NULL, delim);
    }
    free(four_cpy);
    for (size_t i = 0; i < 10; ++i)
    {
        char *digit = (char *)(str_stream + 8 * i);
        size_t digit_i_len = strlen(digit);
        if (digit_i_len == 5)
        {
            // find segments[1] and segments[3]
            char *s1 = strchr(digit, four_minus_one[0]);
            char *s3 = strchr(digit, four_minus_one[1]);
            if ((bool) s1 ^ (bool) s3)
            {
                if (s1)
                {
                    segments[3] = four_minus_one[0];
                    segments[1] = four_minus_one[1];
                }
                else
                {
                    segments[1] = four_minus_one[0];
                    segments[3] = four_minus_one[1];
                }
            }
        }
        else if (digit_i_len == 6)
        {
            // find six
            bool issix = (bool)strchr(digit, one[0]) ^ (bool)strchr(digit, one[1]);
            if (issix)
                strcpy(six, digit);
        }
    }

    if (strchr(six, one[0]))
    {
        segments[5] = one[0];
        segments[2] = one[1];
    }
    else
    {
        segments[5] = one[1];
        segments[2] = one[0];
    }
    for (size_t i = 0; i < 10; ++i)
    {
        char *digit = (char *)(str_stream + 8 * i);
        size_t digit_i_len = strlen(digit);

        char *s1 = strchr(digit, four_minus_one[0]);
        char *s3 = strchr(digit, four_minus_one[1]);
        if (digit_i_len == 5)
        {
            if ((bool) s1 && (bool) s3)
            {
                char *five_minus_found_segs = malloc(5);
                memset(five_minus_found_segs, 0, 5);
                char *digit_cpy = strdup(digit);
                char *tok = strtok(digit_cpy, segments);
                while (tok)
                {
                    five_minus_found_segs = strcat(five_minus_found_segs, tok);
                    tok = strtok(NULL, segments);
                }
                free(digit_cpy);
                segments[6] = *five_minus_found_segs;
                free(five_minus_found_segs);
            }
        }
    }
    free(four_minus_one);

    int sum = SUM_A_TO_G;
    for (size_t i = 0; i < 7; i++)
    {
        if (segments[i] != ' ')
            sum -= segments[i];
    }
    segments[4] = sum;

    return segments;
}


void part1(void)
{
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        fprintf(stderr, "Unable to open file %s\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    size_t count_of_digits = 0;

    size_t limit = 150;
    char *lineptr = malloc(limit);
    if (!lineptr)
    {
        fprintf(stderr, "malloc\n");
        exit(EXIT_FAILURE);
    }

    while ((getline(&lineptr, &limit, fp) > 0))
    {
        strtok(lineptr, "|");
        char *output = strtok(NULL, "|");
        if (!output)
        {
            fprintf(stderr, "strtok error\n");
            exit(EXIT_FAILURE);
        }
        char *digit = strtok(output, " ");
        while (digit)
        {
            digit = stripspace(digit);
            size_t digit_len = strlen(digit);
            switch(digit_len)
            {
                case 2: case 3: case 4: case 7:
                    count_of_digits++;
                    break;
            }
            digit = strtok(NULL, " ");
        }
    }
    free(lineptr);
    printf("part1 answer: %lu\n", count_of_digits);
}


char * stripspace(char *str)
{
    while (isspace(*str))
        str++;

    size_t str_len = strlen(str);
    for (size_t i = str_len; i > 0; i--)
    {
        if (isspace(str[i]))
            str[i] = '\0';
    }
    return str;
}


// This function grabs chars in magnet and
// returns first first occured non captured char
// from str
char select_non_match_char(char *str, char *magnet)
{
    if (str == NULL || strlen(str) == 0 || magnet == NULL || strlen(magnet) == 0)
    {
        fprintf(stderr, "%s: invalid string\n", __func__);
        errno = EINVAL;
        return 0;
    }

    // I can optimize this with some sort of seen
    // list to stop iterating through entire string.
    for (size_t i = 0; i < strlen(str); i++)
    {
        char *found = strchr(magnet, str[i]);
        if (found == NULL)
            return str[i];
    }
    return 0;
}


// stolen from cs50
// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
