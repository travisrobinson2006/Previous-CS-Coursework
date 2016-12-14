#include<iostream>
#include<stdlib.h>

int main()
{
    int ARRAY_SIZE = 10;
    int randArray[ARRAY_SIZE];

    for(int index = 0; index<ARRAY_SIZE;index++)
    {
        randArray[index] = rand() % 1001 - 500;
    }

    for(int index = 0; index<ARRAY_SIZE;index++)
    {
        std::cout<<randArray[index]<<"\n";
    }

    return 0;
}
