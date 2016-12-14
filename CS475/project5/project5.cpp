#include "simd.p5.cpp"
#include <stdio.h>
#include <omp.h>

int main()
{
//    int length = 100000;
//    float A[length];
//    float B[length];
//    float C[length];

    float *pA = new float[length];
    float *pB = new float[length];
    float *pC = new float[length];

//    pA=A;
//    pB=B;
//    pC=C;

    double time0 = omp_get_wtime();
    SimdMul(pA,pB,pC,length);
    double time1 = omp_get_wtime();
    double time = time1-time0;
    double megaCalcsSIMD = (double(length)/time)/1000000;
//    fprintf(stdout,"SIMDMUL MegaCalcs per second: %f\n",megaCalcsSIMD);

    time0 = omp_get_wtime();
    for (int i = 0; i < length; i++)
    {
        pC[i] = pA[i] * pB[i];
    }
    time1 = omp_get_wtime();
    time = time1-time0;
    double megaCalcsNonSIMD = (double(length)/time)/1000000;
//    fprintf(stdout,"NonSIMDMUL MegaCalcs per second: %f\n",megaCalcsNonSIMD);
    fprintf(stdout,"Improvement Non-Reduction: %f\n",(megaCalcsSIMD/megaCalcsNonSIMD));


    time0 = omp_get_wtime();
    double result = SimdMulSum(pA,pB,length);
    time1 = omp_get_wtime();
    time = time1-time0;
    megaCalcsSIMD = (double(length)/time)/1000000;
//    fprintf(stdout,"SIMDMULSUM MegaCalcs per second: %f\n",megaCalcsSIMD);
    double sum = 0;
    time0 = omp_get_wtime();
    for (int i = 0; i < length; i++)
    {
        sum = sum + (pA[i] * pB[i]);
    }
    time1 = omp_get_wtime();

    time = time1-time0;
    megaCalcsNonSIMD = (double(length)/time)/1000000;
//    fprintf(stdout,"NonSIMDMULSUM MegaCalcs per second: %f\n",megaCalcsNonSIMD);

    fprintf(stdout,"Improvement Reduction: %f\n",megaCalcsSIMD/megaCalcsNonSIMD);

    return 0;
}
