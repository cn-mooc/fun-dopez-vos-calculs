using namespace std;
// ==================================================================================================================================
// Little helping tools
// ====================
bool getOptions( int argc, char *argv[], int &m, int &k, int &n) 
{
   int nb_arg = 1;
   bool show = false;
   while (nb_arg < argc)
   {
      char *option = argv[nb_arg];
      if (option[0] == '-')
      {
         switch (option[1])
         {
            case 'k':
            {
               ++nb_arg;
               if (nb_arg < argc)
                  k = atoi(argv[nb_arg]);
               else
               {
                  cout << "option -k require a int argument " << endl;
                  throw -3796;
               }
               break;
            }
            case 'm':
            {
               ++nb_arg;
               if (nb_arg < argc)
                  m = atoi(argv[nb_arg]);
               else
               {
                  cout << "option -m require a int argument " << endl;
                  throw -3496;
               }
               break;
            }
            case 'n':
            {
               ++nb_arg;
               if (nb_arg < argc)
                  n = atoi(argv[nb_arg]);
               else
               {
                  cout << "option -n require a int argument " << endl;
                  throw -3796;
               }
               break;
            }
            case 'p':
            {
               show = true;
               break;
            }
            default:
            {
               cout << "unknown option !!! " << option << endl;
               throw -3456;
            }
         };
      }
      else
      {
         cout << "unknown option !!! " << option << endl;
         cout << "available:" << endl;
         cout << "          -m  <int>   : number of row of A" << endl;
         cout << "          -k  <int>   : number of column of A" << endl;
         cout << "          -n  <int>   : number of column of B" << endl;
         cout << "          -p          : printing with small dimension" << endl;
         throw -3456;
      }
      ++nb_arg;
   }
   if (show)
   {
      m = 11;
      k = 7;
      n = 2;
   }
   return show;
}
// ====================
void printMat(const char *s, const double *C, int M, int N)
{
   cout << s << endl;

   for (int i = 0; i < M; ++i)
   {
      cout << "[" << C[i];
      for (int j = 1; j < N; ++j)
      {
        cout << ", " << C[j * M + i];
      }
      cout << "]" << endl;
   }
}
// ==================================================================================================================================
// BLAS 
// ======
extern "C" void dgemm_(const char *TRANSA, const char *TRANSB, const int *M, const int *N, const int *K, const double *alpha,
                       const double *A, const int *LDA, const double *B, const int *LDB, const double *beta, double *C,
                       const int *LDC);
// ==================================================================================================================================
// BLACS 
// ======
extern "C" void Cblacs_get(int ConTxt, int what, int *val);
extern "C" int   Cblacs_gridinit(int *ConTxt, const char *order, int nprow, int npcol);
extern "C" void  Cblacs_gridinfo(int ConTxt, const int *nprow, const int *npcol, int *myrow, int *mycol);

// ==================================================================================================================================
// SCALAPACK
// =========
extern "C" void descinit_( int*DESCA, int*M, int*N, int*MB, int*NB, int*IRSRC, int *ICSRC, int *ICTXT, int *LLD, int *INFO );
extern "C" void Cpdgemr2d( int m, int n, double *ptrmyblock, int ia, int ja, int *ma, double *ptrmynewblock, int ib, int jb, int * mb, int globcontext );
extern "C" int numroc_(const int *n, const int *nb, const int *iproc, const int *isrcproc, const int *nprocs);

// ==================================================================================================================================
// PBLAS 
// ======
extern "C" void pdgemm_(const char *TRANSA, const char *TRANSB, const int *M, const int *N, const int *K, const double *ALPHA,
                        const double *A, const int *IA, const int *JA, const int *DESCA, const double *B, const int *IB,
                        const int *JB, const int *DESCB, const double *BETA, double *C, const int *IC, const int *JC,
                        const int *DESCC);
