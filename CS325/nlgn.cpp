#include <stdio.h>
#include <math.h>

int main()
{
    long long int x;
    long long int n = 1;

    printf("I find n for n*lg(n) = x \n");
    printf("Enter your target number, x (whole number please): ");
    scanf("%d",&x);

    while((n*log2(n)) < x)
    {
        printf("%d\n",n);
        n = n+1;
    }

    return 0;
}
