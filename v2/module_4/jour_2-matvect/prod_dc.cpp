#include <cmath>
#include <iostream>
using namespace std;

double v1(const double *A, int M, int K)
{
   double r = 0.;
   for (int i = 0; i < M; ++i)
   {
      for (int j = 0; j < K; ++j)
      {
         r += pow(A[j * M + i], 2.);
      }
   }
   return sqrt(r);
}
double v2(const double *A, int M, int K)
{
   double r = 0.;
   for (int j = 0; j < K; ++j)
   {
      for (int i = 0; i < M; ++i)
      {
         r += pow(A[j * M + i], 2.);
      }
   }
   return sqrt(r);
}
int main()
{
   int m = 20000;
   cout << "Allocation matrice A " << m << "x" << m << endl;
   double *A = new double[m * m];

   fill(A, A + m * m, 1.);
   clock_t ta;
   ta = clock();
   cout << "v1 " << v1(A, m, m);
   ta = clock() - ta;
   cout << " " << (ta * 1.) / CLOCKS_PER_SEC << endl;
   ta = clock();
   cout << "v2 " << v2(A, m, m);
   ta = clock() - ta;
   cout << " " << (ta * 1.) / CLOCKS_PER_SEC << endl;
}
