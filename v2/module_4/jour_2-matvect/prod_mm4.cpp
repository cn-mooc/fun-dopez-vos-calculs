#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "externalLib.h"
#include "mpi.h"

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
void MatMatProd(int M, int N, int K, const double *A, const double *B, double *C)
{
   for (int k = 0; k < N; ++k)
   {
      for (int j = 0; j < K; ++j)
      {
         double bjk = B[k * K + j];
         for (int i = 0; i < M; ++i)
         {
            C[k * M + i] += A[j * M + i] * bjk;
         }
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
void MatMatProdPBLAS(int M, int N, int K, const int *descA, const int *descB, const int *descC, const double *A, const double *B,
                     double *C)
{
   double UN = 1.;
   int UNi = 1;
   double ZERO = 0.;
   pdgemm_("No transpose", "No transpose", &M, &N, &K, &UN, A, &UNi, &UNi, descA, B, &UNi, &UNi, descB, &ZERO, C, &UNi, &UNi,
           descC);
}
void withPBlas(int M, int N, int K, int nb_proc, int BLOCKR, int BLOCKC, double &t0, double &t1, bool show)
{
   t0 = MPI_Wtime();
   t1 = 0.;

   int npcol = sqrt(nb_proc);
   int nprow = nb_proc / npcol;

   int ictxt, myrow, mycol;
   int un = 1, zero = 0, info;
   Cblacs_get(-1, 0, &ictxt);
   Cblacs_gridinit(&ictxt, "Row-major", nprow, npcol);
   Cblacs_gridinfo(ictxt, &nprow, &npcol, &myrow, &mycol);
   cout << "myrow and mycol in  proccess grid " << nprow << "x" << npcol << " is: " << myrow << "," << mycol << endl;

   vector<double> A_d;
   vector<double> B_d;
   vector<double> C_d;

   if (myrow > -1)
   {
      int nbrowa = numroc_(&M, &BLOCKR, &myrow, &zero, &nprow);
      int nbcola = numroc_(&K, &BLOCKC, &mycol, &zero, &npcol);
      vector<double> A_d(nbrowa * nbcola + 1);
      if (nbrowa * nbcola)
      {
         cout << "nbrowa " << nbrowa << " nbcola " << nbcola << endl;
         int br = nbrowa / BLOCKR;
         int bc = nbcola / BLOCKC;
         br += (nbrowa % BLOCKR) ? 1 : 0;
         bc += (nbcola % BLOCKC) ? 1 : 0;
         int di = 0;
         for (int r = 0; r < br; ++r)
         {
            int i = r * BLOCKR * nprow + myrow * BLOCKR;
            int fi = i + BLOCKR;
            fi = (fi > M) ? M : fi;
            for (; i < fi; ++i)
            {
               int dj = 0;
               for (int c = 0; c < bc; ++c)
               {
                  int j = c * BLOCKC * npcol + mycol * BLOCKC;
                  int fj = j + BLOCKC;
                  fj = (fj > K) ? K : fj;
                  for (; j < fj; ++j)
                  {
                     A_d[di + dj] = i + j + 1;
                     dj += nbrowa;
                  }
               }
               ++di;
            }
         }
         if (show) printMat("A_d", &A_d[0], nbrowa, nbcola);
      }

      int descA[9];
      int ld = (nbrowa > 1) ? nbrowa : 1;
      descinit_(descA, &M, &K, &BLOCKR, &BLOCKC, &zero, &zero, &ictxt, &ld, &info);

      int nbrowb = numroc_(&K, &BLOCKR, &myrow, &zero, &nprow);
      int nbcolb = numroc_(&N, &BLOCKC, &mycol, &zero, &npcol);
      vector<double> B_d(nbrowb * nbcolb + 1);
      if (nbrowb * nbcolb)
      {
         cout << "nbrowb " << nbrowb << " nbcolb " << nbcolb << endl;
         int br = nbrowb / BLOCKR;
         int bc = nbcolb / BLOCKC;
         br += (nbrowb % BLOCKR) ? 1 : 0;
         bc += (nbcolb % BLOCKC) ? 1 : 0;
         int di = 0;
         for (int r = 0; r < br; ++r)
         {
            int i = r * BLOCKR * nprow + myrow * BLOCKR;
            int fi = i + BLOCKR;
            fi = (fi > K) ? K : fi;
            for (; i < fi; ++i)
            {
               int dj = 0;
               for (int c = 0; c < bc; ++c)
               {
                  int j = c * BLOCKC * npcol + mycol * BLOCKC;
                  int fj = j + BLOCKC;
                  fj = (fj > N) ? N : fj;
                  for (; j < fj; ++j)
                  {
                     B_d[di + dj] = i + j + 1;
                     dj += nbrowb;
                  }
               }
               ++di;
            }
         }
         if (show) printMat("B_d", &B_d[0], nbrowb, nbcolb);
      }
      int descB[9];
      ld = (nbrowb > 1) ? nbrowb : 1;
      descinit_(descB, &K, &N, &BLOCKR, &BLOCKC, &zero, &zero, &ictxt, &ld, &info);

      int nbrowc = numroc_(&M, &BLOCKR, &myrow, &zero, &nprow);
      int nbcolc = numroc_(&N, &BLOCKC, &mycol, &zero, &npcol);
      vector<double> C_d(nbrowc * nbcolc + 1);
      if (nbrowc * nbcolc) cout << "nbrowc " << nbrowc << " nbcolc " << nbcolc << endl;

      int descC[9];
      ld = (nbrowc > 1) ? nbrowc : 1;
      descinit_(descC, &M, &N, &BLOCKR, &BLOCKC, &zero, &zero, &ictxt, &ld, &info);

      cout << "Calcul C=A.B (PBLAS)" << endl;
      t0 = MPI_Wtime() - t0;
      t1 = MPI_Wtime();
      MatMatProdPBLAS(M, N, K, descA, descB, descC, &A_d[0], &B_d[0], &C_d[0]);
      t1 = MPI_Wtime() - t1;

      if (show && nbrowc * nbcolc) printMat("C_d", &C_d[0], nbrowc, nbcolc);
   }
   else
      t0 = MPI_Wtime() - t0;
}

int main(int argc, char *argv[])
{
   MPI_Init(&argc, &argv);
   double t0 = MPI_Wtime();

   int m = 5000;
   int k = 5000;
   int n = 3000;
   int BLOCKR = 100;
   int BLOCKC = 50;
   const bool show = getOptions(argc, argv, m, k, n);

   int nb_proc, proc_id;
   MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
   MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

   if (!show)
   {
      string no = "output_main4_" + std::to_string(proc_id) + ".txt";
      if (proc_id > 50)
         freopen("/dev/null", "w", stdout);
      else
         freopen(no.c_str(), "w", stdout);
   }
   else
   {
      BLOCKR = 3;
      BLOCKC = 2;
   }

   int stride = m / nb_proc;
   int shift = stride * proc_id + 1;
   if (proc_id == nb_proc - 1) stride += m % nb_proc;

   cout << "Allocation matrice A " << stride << "x" << k << endl;
   double *A = new double[stride * k];
   cout << "Allocation matrice B " << k << "x" << n << endl;
   double *B = new double[k * n];
   cout << "Allocation matrice C " << stride << "x" << n << endl;
   double *C = new double[stride * n];

   double t1 = MPI_Wtime();
   setMat(stride, n, k, &A[0], &B[0], &C[0], shift);
   t1 = MPI_Wtime() - t1;

   if (show)
   {
      printMat("A", &A[0], stride, k);
      printMat("B", &B[0], k, n);
   }

   cout << "Calcul C=A.B" << endl;
   double t2 = MPI_Wtime();
   MatMatProd(stride, n, k, &A[0], &B[0], &C[0]);
   t2 = MPI_Wtime() - t2;

   MPI_Barrier(MPI_COMM_WORLD);
   if (show) printMat("C", &C[0], stride, n);

   cout << "Calcul C=A.B (blas)" << endl;
   double t3 = MPI_Wtime();
   MatMatProdBLAS(stride, n, k, &A[0], &B[0], &C[0]);
   t3 = MPI_Wtime() - t3;

   MPI_Barrier(MPI_COMM_WORLD);
   if (show) printMat("C", &C[0], stride, n);

   cout << "Liberation memoire" << endl;
   delete[] A;
   delete[] B;
   delete[] C;

   double t5, t6;
   double t4 = MPI_Wtime();
   withPBlas(m, n, k, nb_proc, BLOCKR, BLOCKC, t5, t6, show);
   t4 = MPI_Wtime() - t4;

   if (show) printMat("C", &C[0], stride, n);

   t0 = MPI_Wtime() - t0;
   cout << "Elapse time in s: " << t0 << endl;
   cout << "Elapse time in %:" << endl;
   //cout << "setMat: " << 100. * t1 / t0 << endl;
   cout << "MatMatProd: " << 100. * t2 / t0 << endl;
   cout << "MatMatProdBLAS: " << 100. * t3 / t0 << endl;
   //cout << "withPBlas: " << 100. * t4 / t0 << endl;
   //cout << "withPBlas, setMat: " << 100. * t5 / t0 << endl;
   cout << "MatMatProdPBLAS: " << 100. * t6 / t0 << endl;
   MPI_Finalize();
   return 0;
}
