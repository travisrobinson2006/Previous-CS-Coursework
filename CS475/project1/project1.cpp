//Travis Robinson
//CS475
//Spring 2016
//Project1
//OpenMP: Numeric Integration with OpenMP

#include <omp.h>
#include <stdio.h>
#include <math.h>

#define XMIN 0.
#define XMAX 3.
#define YMIN 0.
#define YMAX 3.

#define Z00	0.
#define Z10	1.
#define Z20	0.
#define Z30	0.

#define Z01	1.
#define Z11	6.
#define Z21	1.
#define Z31	0.

#define Z02	0.
#define Z12	1.
#define Z22	0.
#define Z32	4.

#define Z03	3.
#define Z13	2.
#define Z23	3.
#define Z33	3.

//#define NUMT 8
//#define NUMS 9000

float Height( int, int );
int main( )
{
	#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
	#endif

	// the area of a single full-sized tile:

	float fullTileArea = (  ( (XMAX-XMIN)/(float)(NUMS-1) )  *  ( ( YMAX - YMIN )/(float)(NUMS-1) )  );
//	float fullTileArea = (XMAX-XMIN)*(YMAX-YMIN)/((float)NUMS*(float)NUMS);
	// sum up the weighted heights into the variable "volume"
	// using an OpenMP for loop and a reduction

	omp_set_num_threads(NUMT);

	float sum_volume = 0.;

	double time0 = omp_get_wtime();
	#pragma omp parallel for collapse(2) default(none),shared(fullTileArea),reduction(+:sum_volume)
	for(int iv = 0; iv < NUMS; iv++ )
	{
		for (int iu = 0; iu < NUMS; iu++)
		{
			float area = fullTileArea;
			float height = Height(iu,iv);
			if(iu == XMIN || iu == XMAX)
			{
				area = area / 2;
			}
			if (iv == YMIN || iv == YMAX)
			{
				area = area / 2;
			}

			float volume = area * height;
			sum_volume = sum_volume + volume;
		}
	}

	double time1 = omp_get_wtime();
	fprintf(stdout,"Elapsed time = %10.2lf microseconds\n",1000000. * (time1 - time0));
	double time = time1 - time0; //seconds taken
	double volumes_per_second =( (float) NUMS * (float) NUMS ) / time;
	fprintf(stdout,"Volumes computed per second: %10.2lf \n",volumes_per_second);
	printf("Calculated Volume: %f\n",sum_volume);
	return 0;
}


float Height( int iu, int iv )	// iu,iv = 0 .. NUMS-1
{
	float u = (float)iu / (float)(NUMS-1);
	float v = (float)iv / (float)(NUMS-1);

	// the basis functions:

	float bu0 = (1.-u) * (1.-u) * (1.-u);
	float bu1 = 3. * u * (1.-u) * (1.-u);
	float bu2 = 3. * u * u * (1.-u);
	float bu3 = u * u * u;

	float bv0 = (1.-v) * (1.-v) * (1.-v);
	float bv1 = 3. * v * (1.-v) * (1.-v);
	float bv2 = 3. * v * v * (1.-v);
	float bv3 = v * v * v;

	// finally, we get to compute something:

	float height = 	  bu0 * ( bv0*Z00 + bv1*Z01 + bv2*Z02 + bv3*Z03 )
			+ bu1 * ( bv0*Z10 + bv1*Z11 + bv2*Z12 + bv3*Z13 )
			+ bu2 * ( bv0*Z20 + bv1*Z21 + bv2*Z22 + bv3*Z23 )
			+ bu3 * ( bv0*Z30 + bv1*Z31 + bv2*Z32 + bv3*Z33 );

	return height;
}

