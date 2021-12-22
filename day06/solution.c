/* 
 * faster solution
 * /
#include <stdio.h>

#define NO_DAYS 256
#define MAX_HATCH_DELAY 8
#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))

void print_fish(long *fishes_days);

int main(void)
{
    long fishes_days[MAX_HATCH_DELAY + 1] = {0};
    int input[] = {
        1,5,5,1,5,1,5,3,1,3,2,4,3,4,1,1,3,5,4,4,2,1,
        2,1,2,1,2,1,5,2,1,5,1,2,2,1,5,5,5,1,1,1,5,1,
        3,4,5,1,2,2,5,5,3,4,5,4,4,1,4,5,3,4,4,5,2,4,
        2,2,1,3,4,3,2,3,4,1,4,4,4,5,1,3,4,2,5,4,5,3,
        1,4,1,1,1,2,4,2,1,5,1,4,5,3,3,4,1,1,4,3,4,1,
        1,1,5,4,3,5,2,4,1,1,2,3,2,4,4,3,3,5,3,1,4,5,
        5,4,3,3,5,1,5,3,5,2,5,1,5,5,2,3,3,1,1,2,2,4,
        3,1,5,1,1,3,1,4,1,2,3,5,5,1,2,3,4,3,4,1,1,5,
        5,3,3,4,5,1,1,4,1,4,1,3,5,5,1,4,3,1,3,5,5,5,
        5,5,2,2,1,2,4,1,5,3,3,5,4,5,4,1,5,1,5,1,2,5,
        4,5,5,3,2,2,2,5,4,4,3,3,1,4,1,2,3,1,5,4,5,3,
        4,1,1,2,2,1,2,5,1,1,1,5,4,5,2,1,4,4,1,1,3,3,
        1,3,2,1,5,2,3,4,5,3,5,4,3,1,3,5,5,5,5,2,1,1,
        4,2,5,1,5,1,3,4,3,5,5,1,4,3
    };
    size_t input_len = ARR_LEN(input);
    for (size_t i = 0; i < input_len; ++i)
    {
        fishes_days[input[i]]++;
    }

    printf("init fishes_days: \n");
    print_fish(fishes_days);

    size_t counter = 0;
    for (size_t i = 0; i < NO_DAYS; ++i, counter++)
    {
        long fishes_days0 = fishes_days[0];
        fishes_days[0] -= fishes_days0;
        for (size_t j = 1; j < MAX_HATCH_DELAY + 1; ++j)
        {
            long fishes_day_cur = fishes_days[j];
            fishes_days[j - 1] += fishes_day_cur;;
            fishes_days[j] -= fishes_day_cur;
        }
        fishes_days[6] += fishes_days0;
        fishes_days[8] += fishes_days0;
    }

    printf("counter: %ld\n", counter);
    printf("\noutput: \n");
    print_fish(fishes_days);
    long sum = 0;
    for (int i = 0; i < 9; i++)
    {
        sum += fishes_days[i];
    }
    printf("\nanswer: %ld\n", sum);
    return 0;
}

void print_fish(long *fishes_days)
{
    for (int i = 0; i < 9; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < 9; i++)
    {
        printf("%ld ", fishes_days[i]);
    }
}
