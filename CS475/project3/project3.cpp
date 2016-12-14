//Travis Robinson
//CS475
//Spring 2016
//Project 3
#include <omp.h>
#include <stdio.h>
#include <math.h>


struct s
{
	float value;
	int pad[NUM];//commented out for fix #2
} Array[4];

int main()
{
//	. . .

	omp_set_num_threads( NUMT );

	unsigned int someBigNumber = 1000000000;	// if > 4B, use "long unsigned int"


   	double time0 = omp_get_wtime();

	#pragma omp parallel for
	for( int i = 0; i < 4; i++ )
	{
//	    float tmp = Array[i].value;
		for( unsigned int j = 0; j < someBigNumber; j++ )
		{
			Array[ i ].value = Array[ i ].value + 2.;
//        		tmp = tmp+2;
		}
//		Array[i].value = tmp;
	}

   	double time1 = omp_get_wtime();
    double time = time1 - time0;

    printf("Mega-Calculations per second: %10.2lf\n",((float)4 * (float)someBigNumber / time)/1000000);

}
