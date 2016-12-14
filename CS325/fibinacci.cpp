#include <stdio.h>
#include <time.h>

using namespace std;

int fibRecur (int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return (fibRecur(n-1)+fibRecur(n-2));
    }
}

int fibIter (int n)
{
    int fib = 0;
    int a = 1;
    int t = 0;
    for (int k = 1; k < n; k++)
    {
        t = fib + 1;
        a = fib;
        fib = t;
    }
    return fib;
}

int main ()
{
    int n, result;

    for (int count = 1; count < 11; count++)
    {
        clock_t tStart = clock();
        fibIter(count*100000000); //change to fibRecur
        printf("n = %d",(count*100000000));
        printf("Time taken: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    }
    return 0;
}
