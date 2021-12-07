// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INPUT_FILE_NAME "input.txt"
size_t fillArray(FILE *input_file);

int arr[1024 * 4];

int main(void)
{
    FILE *input_fp = fopen(INPUT_FILE_NAME, "r");
    if (!input_fp)
    {
        fprintf(stderr, "Error: can't able to open the file '%s': %s\n",
                INPUT_FILE_NAME, strerror(errno));
        exit(1);
    }
       
    size_t len = fillArray(input_fp);
    size_t count_of_increase = 0;
    for (size_t i = 1; i < len; i++)
    {
        if (arr[i - 1] < arr[i])
        {
            count_of_increase++;
        }
    }
    printf("answer: %ld\n", count_of_increase);

    return 0;
}

size_t fillArray(FILE *input_filep)
{
    if (!input_filep)
    {
        fprintf(stderr, "Error: input_file should not be null\n");
        exit(1);
    }

    int c = 0;
    char number_str[10];
    size_t idx = 0;
    for (int i = 0; (c = fgetc(input_filep)) != EOF; i++)
    {
        if (c == '\n')
        {
            number_str[i] = '\0';
            i = -1;
            arr[idx++] = (int) atoi(number_str);
            continue;
        }
        number_str[i]  = (char)c;
    }
    return idx;
}

