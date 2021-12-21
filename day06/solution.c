#include <stdio.h>

#define NO_DAYS 18
#define MAX_HATCH_DELAY 8
#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))


int main(void)
{
    long fishes_days[MAX_HATCH_DELAY + 1] = {0};
    (void) fishes_days;
    int input[] = {1, 2, 3, 3, 4};
    size_t input_len = ARR_LEN(input);
    /* printf("array_len: %lu\n", */ 
    for (size_t i = 0; i < input_len; ++i)
    {
        fishes_days[input[i]]++;
    }
    printf("fishes_days: \n");
    for (int i = 0; i < MAX_HATCH_DELAY + 1; ++i)
    {
        printf("%ld ", fishes_days[i]);
    }
    printf("\n");
    for (size_t i = 0; i < NO_DAYS; ++i)
    {
        if (fishes_days[0] > 0)
        {
            long fishes_days0 = fishes_days[0];
            fishes_days[0] = 0;
            fishes_days[6] += fishes_days0;
            fishes_days[8] += fishes_days0;
            printf("d 6: %ld\n", fishes_days[6]);
        }
        else
        {
            for (size_t j = 1; j < MAX_HATCH_DELAY; ++j)
            {
                fishes_days[j - 1] += fishes_days[j];
                fishes_days[j] -= fishes_days[j];
            }
        }
    }
    return 0;
}
