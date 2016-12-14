#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cmath>
#include <omp.h>

const int SANTAS_HARVEST = 8;
const float SANTA_FERTILIZES = 1.05;

const float GRAIN_GROWS_PER_MONTH =		8.0;
const float ONE_DEER_EATS_PER_MONTH =		0.5;

const float AVG_PRECIP_PER_MONTH =		6.0;
const float AMP_PRECIP_PER_MONTH =		6.0;
const float RANDOM_PRECIP =			2.0;

const float AVG_TEMP =				50.0;
const float AMP_TEMP =				20.0;
const float RANDOM_TEMP =			10.0;

    int	NowYear;		// 2016 - 2021
    int	NowMonth;		// 0 - 11

    float	NowPrecip;		// inches of rain per month
    float	NowTemp;		// temperature this month
    float	NowHeight;		// grain height in inches
    int	NowNumDeer;		// number of deer in the current population

    int NumberOfHarvests = 0;

float Ranf( float low, float high )
{
        float r = (float) rand( );               // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int Ranf( int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(low,high) );
}


void GrainDeer()
{
    //GrainDeer( );
    int CarryingCapacity, tempDeerCount;
    while (NowYear < 2022)
    {
        tempDeerCount = NowNumDeer;
        CarryingCapacity = NowHeight;
        if (tempDeerCount < CarryingCapacity)
        {
            tempDeerCount++;
        }
        else if (tempDeerCount > CarryingCapacity)
        {
            tempDeerCount--;
        }

        // DoneComputing barrier:
        #pragma omp barrier
        NowNumDeer = tempDeerCount;

        // DoneAssigning barrier:
        #pragma omp barrier

        //Santas Harvest Barrier
        #pragma omp barrier


        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Grain( )
{
    //Grain( );
    float tempFactor;
    float precipFactor;
    while (NowYear < 2022)
    {
//        fprintf(stdout,"NowTemp: %f\n",NowTemp);
//        fprintf(stdout,"NowPrecip: %f\n",NowPrecip);
        tempFactor = exp(-1*pow(((NowTemp - AVG_TEMP)/10.0),2.0));
        precipFactor = exp(-1*pow(((NowPrecip - AVG_PRECIP_PER_MONTH)/10.0),2.0));
//        fprintf(stdout,"tempFactor: %f\n",tempFactor);
//        fprintf(stdout,"precipFactor: %f\n",precipFactor);


        // DoneComputing barrier:
        #pragma omp barrier
        NowHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        NowHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        if (NowHeight < 0.)
        {
            NowHeight = 0.;
        }

        // DoneAssigning barrier:
        #pragma omp barrier

        //Santas Harvest Barrier
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Watcher( )
{
    //Watcher( );

    while (NowYear < 2022)
    {
        // DoneComputing barrier:
        #pragma omp barrier

        // DoneAssigning barrier:
        #pragma omp barrier

        //Santas Harvest Barrier
        #pragma omp barrier

        fprintf(stdout, "Month %d Year %d:\n",NowMonth,NowYear);
        fprintf(stdout,"Temperature: %f\n",((NowTemp-32)*(5./9.)));
        fprintf(stdout,"Precipitation: %f\n",NowPrecip);
        fprintf(stdout, "Number of Graindeer: %d\n",NowNumDeer);
        fprintf(stdout,"Height: %f\n",(NowHeight*2.54));
        fprintf(stdout,"Accumulated Harvest Count: %d\n",NumberOfHarvests);

        NowMonth++;
        if (NowMonth > 11)
        {
            NowMonth = 0;
            NowYear++;
        }

        //calculate initial temp
        float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

        float temp = AVG_TEMP - AMP_TEMP * cos( ang );
        NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
        NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
        if( NowPrecip < 0. )
            NowPrecip = 0.;
        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void MyAgent( )
{
    while(NowYear < 2022)
    {

        // DoneComputing barrier:
        #pragma omp barrier

        // DoneAssigning barrier:
        #pragma omp barrier

        //Santas Harvest Barrier
        #pragma omp barrier
        if (NowNumDeer >= SANTAS_HARVEST) //Santa gathers his team
        {
            NowNumDeer = NowNumDeer - SANTAS_HARVEST;
            NumberOfHarvests++;
        }
        NowHeight = NowHeight * SANTA_FERTILIZES;//Santa fertilizes his grain


        // DonePrinting barrier:
        #pragma omp barrier
    }
}

int main()
{
    //calculate initial temp
    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
    if( NowPrecip < 0. )
        NowPrecip = 0.;

    omp_set_num_threads( 4 );

    NowYear = 2016;
    NowMonth = 0;
    NowHeight = 1.0;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            GrainDeer( );
        }

        #pragma omp section
        {
            Grain( );
        }

        #pragma omp section
        {
            Watcher( );
        }

        #pragma omp section
        {
            MyAgent( );
        }
    }



    return 0;
}
