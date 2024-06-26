#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int arr[] = {7, 2, 5, 3, 1, 0, 4, 6};
    printf("Unsorted array :\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
    for (int i = 0; i < 7; i++)
    {
        int min = arr[i];
        int index = i;
        for (int j = i + 1; j < 7; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[index];
        arr[index] = temp;
    }
    printf("Sorted array: \n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}
