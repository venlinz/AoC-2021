#include <stdio.h>
#include <unistd.h>

void printarray(int *a, size_t len);

int main(void)
{
    int a[10] = { 1, 5, 2, 7, 2, 9, 3, 32, 4, 6};
    /* int a[10] = {32, 9, 8, 7, 6, 5, 4, 3, 2, 1}; */
    for (int i = 0; i < 10; i++)
        printf("%d\n", a[i]);

    int count = 0;
    printf("sorted\n");
    for (int i = 1; i < 10; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            count++;
            printarray(a, i);
            if (a[j] > a[i])
            {
                int t = a[j];
                a[j] = a[i];
                a[i] = t;
                i--;
            }
            else
            {
                /* sleep(2); */
                putchar('\n');
                break;
            }
            printarray(a, i);
            putchar('\n');
            /* sleep(2); */
        }
    }
    printf("iterations: %d\n",count);
    return 0;

}

void printarray(int *a, size_t len)
{
    for (int i = 0; i < 10; ++i)
    {
        printf("%5d", a[i]);
        if (len == i)
            putchar('*');
        else
            putchar(' ');
    }
    printf("\n");
}
