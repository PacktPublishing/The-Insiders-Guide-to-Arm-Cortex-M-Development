#include <stdio.h>

int dot_product(int v1[], int v2[], int length)
{
    int sum = 0;

    for (int i = 0; i < length; i++)
      sum += v1[i] * v2[i];

    return sum;
}


int main(void)
{
    int len = 3;
    int v1[] = {1, 3, -5};
    int v2[] = {4, -2, -1};

    int dp = dot_product(v1, v2, len);

    printf("Dot product is %d\n", dp);

    return 0;
}
