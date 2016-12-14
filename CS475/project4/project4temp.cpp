#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cmath>
#include <omp.h>


const float GRAIN_GROWS_PER_MONTH =		8.0;
const float ONE_DEER_EATS_PER_MONTH =		0.5;

const float AVG_PRECIP_PER_MONTH =		6.0;
const float AMP_PRECIP_PER_MONTH =		6.0;
const float RANDOM_PRECIP =			2.0;

const float AVG_TEMP =				50.0;
const float AMP_TEMP =				20.0;
const float RANDOM_TEMP =			10.0;

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
int main()
{
    int	NowYear;		// 2016 - 2021
    int	NowMonth;		// 0 - 11

    float	NowPrecip;		// inches of rain per month
    float	NowTemp;		// temperature this month
    float	NowHeight;		// grain height in inches
    int	NowNumDeer;		// number of deer in the current population

    //calculate initial temp
    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
    if( NowPrecip < 0. )
        NowPrecip = 0.;

    omp_set_num_threads( 4 );
    #pragma omp parallel sections
    {
        #pragma omp section
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


                // DonePrinting barrier:
                #pragma omp barrier
            }
        }

        #pragma omp section
        {
            //Grain( );
            int tempFactor;
            int precipFactor;
            while (NowYear < 2022)
            {
                tempFactor = exp(-1*pow(((NowTemp - AVG_TEMP)/10.),2.));
                precipFactor = exp(-1*pow(((NowPrecip - AVG_PRECIP_PER_MONTH)/10.),2.));

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


                // DonePrinting barrier:
                #pragma omp barrier
            }
        }

        #pragma omp section
        {
            //Watcher( );

            while (NowYear < 2022)
            {
                while (NowYear < 2022)
                {
                    // DoneComputing barrier:
                    #pragma omp barrier

                    // DoneAssigning barrier:
                    #pragma omp barrier

                    fprintf(stdout, "Height for Month &d Year %d: %f",NowMonth,NowYear,NowHeight);
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

        }

        #pragma omp section
        {
            //MyAgent( );

            while (NowYear < 2022)
            {

                // DoneComputing barrier:
                #pragma omp barrier


                // DoneAssigning barrier:
                #pragma omp barrier


                // DonePrinting barrier:
                #pragma omp barrier
            }

        }
    }



    return 0;
}
