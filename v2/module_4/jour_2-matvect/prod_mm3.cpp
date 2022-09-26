#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "externalLib.h"

void setMat(int M,  int N, int K, double *A, double *B, double *C, int shift)
{
   for (int i = 0; i < M; ++i)
   {
      for (int j = 0; j < K; ++j)
      {
         A[j * M + i] = i + j + shift;
      }
      for (int k = 0; k < N; ++k)
      {
         C[k * M + i] = 0.;
      }
   }
   for (int j = 0; j < K; ++j)
   {
      for (int k = 0; k < N; ++k)
      {
         B[k * K + j] = j + k + 1;
      }
   }
}
void MatMatProdBLAS(int M, int N, int K, const double *A, const double *B, double *C)
{
   char trans = 'N';
   double UN = 1.;
   double ZERO = 0.;
   dgemm_(&trans, &trans, &M, &N, &K, &UN, A, &M, B, &K, &ZERO, C, &M);
}

int main(int argc, char *argv[])
{
   int m = 5000;
   int k = 10000;
   int n = 300;
   const bool show = getOptions(argc, argv, m, k, n);

   if (!show)
   {
      string no = "output_main3.txt";
      freopen(no.c_str(), "w", stdout);
   }

   cout << "Allocation matrice A " << m << "x" << k << endl;
   double *A = new double[k * m];
   cout << "Allocation matrice B " << k << "x" << n << endl;
   double *B = new double[k * n];
   cout << "Allocation matrice C " << m << "x" << n << endl;
   double *C = new double[m * n];

   cout << "Initialisation matrice A,B,C " << endl;
   setMat(m, n, k, &A[0], &B[0], &C[0], 1);

   if (show)
   {
      printMat("A", &A[0], m, k);
      printMat("B", &B[0], k, n);
   }

   cout << "Calcul C=A.B (blas)" << endl;
   MatMatProdBLAS(m, n, k, &A[0], &B[0], &C[0]);

   if (show) printMat("C", &C[0], m, n);

   cout << "Liberation memoire" << endl;
   delete[] A;
   delete[] B;
   delete[] C;

   return 0;
}
