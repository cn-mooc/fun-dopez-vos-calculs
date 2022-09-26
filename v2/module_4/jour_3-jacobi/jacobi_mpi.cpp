#include <mpi.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void updateX(int Nl, double *x, double *oldx)
{
   for (int i = 0; i < Nl; i++)
   {
      oldx[i] = x[i];
   }
}
void bndComput(int nlc, int nlc2, int nll, int nll2, double h2, double *f, double *x, double *oldx)
{
   for (int i = 0; i < nlc; i++)
   {
      int p;
      p = nlc2 + 1 + i;
      x[p] = 0.25 * (h2 * f[p] + (oldx[p + 1] + oldx[p - 1] + oldx[p + nlc2] + oldx[p - nlc2]));
      p = (nll2 - 2) * nlc2 + 1 + i;
      x[p] = 0.25 * (h2 * f[p] + (oldx[p + 1] + oldx[p - 1] + oldx[p + nlc2] + oldx[p - nlc2]));
   }
   for (int i = 1; i < nll - 1; i++)
   {
      int p;
      p = (i + 1) * nlc2 + 1;
      x[p] = 0.25 * (h2 * f[p] + (oldx[p + 1] + oldx[p - 1] + oldx[p + nlc2] + oldx[p - nlc2]));
      p = (i + 1) * nlc2 + nlc2 - 2;
      x[p] = 0.25 * (h2 * f[p] + (oldx[p + 1] + oldx[p - 1] + oldx[p + nlc2] + oldx[p - nlc2]));
   }
}
void bndUpdate(int nlc, int nlc2, int nll, int nll2, double *x, double *BufferR, int *BTLR_rank)
{
   if (BTLR_rank[0] != -1)
      for (int i = 0; i < nlc; i++) x[0 * nlc2 + 1 + i] = BufferR[0 * nlc + i];
   if (BTLR_rank[1] != -1)
      for (int i = 0; i < nlc; i++) x[(nll2 - 1) * nlc2 + 1 + i] = BufferR[1 * nlc + i];
   if (BTLR_rank[2] != -1)
      for (int i = 0; i < nll; i++) x[(i + 1) * nlc2 + 0] = BufferR[2 * nlc + i];
   if (BTLR_rank[3] != -1)
      for (int i = 0; i < nll; i++) x[(i + 1) * nlc2 + nlc2 - 1] = BufferR[2 * nlc + nll + i];
}

void bufComput(int nlc, int nlc2, int nll, int nll2, double *x, double *BufferS)
{
   for (int i = 0; i < nlc; i++)
   {
      BufferS[0 * nlc + i] = x[nlc2 + 1 + i];
      BufferS[1 * nlc + i] = x[(nll2 - 2) * nlc2 + 1 + i];
   }
   for (int i = 0; i < nll; i++)
   {
      BufferS[2 * nlc + i] = x[(i + 1) * nlc2 + 1];
      BufferS[2 * nlc + nll + i] = x[(i + 1) * nlc2 + nlc2 - 2];
   }
}
double errorComput(int nll2, int nlc2, double *x, double *oldx)
{
   double error_loc = 0.0;
   double error = 0.0;
   for (int i = 1; i < nll2 - 1; i++)
   {
      for (int j = 1; j < nlc2 - 1; j++)
      {
         int p = i * nlc2 + j;
         error_loc += pow(x[p] - oldx[p], 2.0);
      }
   }
   MPI_Allreduce(&error_loc, &error, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
   return sqrt(error);
}
void Comput(int nll2, int nlc2, double *x, double *oldx, double h2, double *f)
{
   for (int i = 1; i < nll2 - 1; i++)
   {
      for (int j = 1; j < nlc2 - 1; j++)
      {
         int p = i * nlc2 + j;
         x[p] = 0.25 * (h2 * f[p] + (oldx[p + 1] + oldx[p - 1] + oldx[p + nlc2] + oldx[p - nlc2]));
      }
   }
}
void write_vtk(int rank, int n, double h, const vector<double> &values, const string &file_name = "toto")
{
   ofstream os(file_name + "_" + std::to_string(rank) + ".vtk");
   os << "# vtk DataFile Version 2.0" << endl;
   os << "Example" << endl;
   os << "ASCII" << endl;
   os << "DATASET STRUCTURED_POINTS" << endl;
   os << "DIMENSIONS " << n << " " << n << " " << 1 << endl;
   os << "ASPECT_RATIO " << h << " " << h << "  " << h << endl;
   os << "ORIGIN 0 0 0" << endl;
   os << "POINT_DATA " << n * n;
   os << "SCALARS u double 1" << endl;
   os << "LOOKUP_TABLE default" << endl;
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++) os << values[i * n + j] << " ";
   }
   os << endl;
}

void write_vti(int rank, int size, int ncl, int ncc, int nll, int nlc, double h, const vector<double> &values,
               const string &file_name = "toto")
{
   // ne marche pas vraiment car les coins ne sont pas des vrais fantomes et donc pas mis a jour !!!!
   if (rank == 0)
   {
      ofstream os(file_name + ".pvti");
      os << "<VTKFile type=\"PImageData\" version=\"1.0\" byte_order=\"LittleEndian\">\n";
      os << "<PImageData WholeExtent=\"0 " << 1 + ncc * (nlc - 2) << " 0 " << 1 + ncl * (nll - 2)
         << " 0 0\" GhostLevel=\"1\" Origin=\"0 0 0\" Spacing=\"1 1 1\">\n";
      os << "<PPointData>\"\n";
      os << "<PointData Scalars=\"u\"></PointData>\n";
      os << "</PPointData>\n";
      for (int i = 0; i < size; i++)
      {
         string fname = file_name + "_" + std::to_string(i) + ".vti";
         int bx = i % ncc * (nlc - 2);
         int by = i / ncc * (nll - 2);
         cout << "uuuu " << bx << " " << by << endl;
         os << "<Piece Extent=\"" << bx << " " << bx + nlc - 1 << " " << by << " " << by + nll - 1 << " 0 0\" Source=\"" << fname
            << "\"/>\n";
      }
      os << "</PImageData>\n";
      os << "</VTKFile>\n";
   }

   int bx = rank % ncc * (nlc - 2);
   int by = rank / ncc * (nll - 2);

   cout << rank << " begin " << bx << " " << by << endl;

   ofstream os(file_name + "_" + std::to_string(rank) + ".vti");
   os << "<VTKFile type=\"ImageData\" version=\"1.0\" byte_order=\"LittleEndian\">" << endl;
   os << "<ImageData WholeExtent=\"" << bx << " " << bx + nlc - 1 << " " << by << " " << by + nll - 1
      << " 0 0\" Origin=\"0.0 0.0 0.0\" Spacing=\"" << h << " " << h << " " << h << "\">" << endl;
   os << "<Piece Extent=\"" << bx << " " << bx + nlc - 1 << " " << by << " " << by + nll - 1 << " 0 0\">" << endl;
   os << "<PointData Scalars=\"u\">" << endl;
   os << "<DataArray type=\"Float64\" Name=\"u\" format=\"ascii\">" << endl;

   for (int i = 0; i < nll; i++)
   {
      for (int j = 0; j < nlc; j++) os << values[i * nlc + j] << " ";
   }
   os << endl;

   os << "</DataArray>" << endl;
   os << "</PointData>" << endl;
   os << "<CellData>" << endl;
   os << "</CellData>" << endl;
   os << "</Piece>" << endl;
   os << "</ImageData>" << endl;
   os << "</VTKFile>" << endl;
}

int main(int argc, char **argv)
{
   MPI_Init(&argc, &argv);

   double a, b;
   a = MPI_Wtime();

   int rank, size;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   int n = 1 << 7;
   int max_iter = 1e7;
   double epsilon = 1e-7;

   int ncsr = std::round(sqrt(size));
   bool found = false;
   while (!found)
   {
      if (size % ncsr == 0)
         found = true;
      else
         ncsr--;
   }
   int ncl = ncsr;
   int ncc = size / ncsr;

   for (int i = 0; i < argc; ++i)
   {
      if (argv[i] == string("-n")) n = stoi(argv[i + 1]);
      if (argv[i] == string("-eps")) epsilon = stoi(argv[i + 1]);
      if (argv[i] == string("-maxiter")) max_iter = stoi(argv[i + 1]);
      if (argv[i] == string("-ncl")) ncl = stoi(argv[i + 1]);
      if (argv[i] == string("-ncc")) ncc = stoi(argv[i + 1]);
   }

   int n2 = n + 2;
   int N = n2 * n2;
   double h = 1.0 / (n + 1);
   double h2 = h * h;

   if (ncl * ncc != size)
   {
      if (rank == 0)
         cout << "Error : ncl * ncc must be egual to the number of cores used : " << ncl << " * " << ncc << " != " << size
              << endl;
      exit(1);
   }
   if (n % ncl != 0 || n % ncc != 0)
   {
      if (rank == 0)
         cout << "Error : n must be a mutiple of ncl and ncc : n= " << n << " ncl= " << ncl << " ncc= " << ncc << endl;
      exit(1);
   }

   int nll = n / ncl;  // number of local rows
   int nlc = n / ncc;  // number of local columns
   int nll2 = nll + 2;
   int nlc2 = nlc + 2;
   int Nl = nll2 * nlc2;

   vector<int> BTLR_rank(4);  // Bottom, top, left , right
   BTLR_rank[0] = rank - ncc;
   BTLR_rank[1] = rank + ncc;
   BTLR_rank[2] = rank - 1;
   BTLR_rank[3] = rank + 1;

   // on the border there is no neigbours (-1)
   if (rank < ncc) BTLR_rank[0] = -1;
   if (rank >= (ncl - 1) * ncc) BTLR_rank[1] = -1;
   if (rank % ncc == 0) BTLR_rank[2] = -1;
   if (rank % ncc == ncc - 1) BTLR_rank[3] = -1;

   if (rank == 0)
   {
      cout << "h= " << h << " " << h2 << endl;
      cout << "rank,size= " << rank << " " << size << endl;
      cout << "ncore= " << ncl << " * " << ncc << endl;
      cout << "N= " << n << " " << n2 << " " << N << endl;
      cout << "Nloc= " << nll << " " << nlc << " " << nll2 << " " << nlc2 << " " << Nl << endl;
      cout << endl;
   }

   /*
     for(int i=0;i<size;i++)
     {
       if(rank==i)
         cout << "rank= " << rank << " BTLR_rank= " << BTLR_rank[0] << " " << BTLR_rank[1] << " " << BTLR_rank[2] << " " <<
     BTLR_rank[3] << endl; MPI_Barrier(MPI_COMM_WORLD);
     }
   */

   vector<double> f(Nl);
   for (int i = 0; i < Nl; i++) f[i] = 1.0;

   vector<double> x(Nl);
   for (int i = 0; i < Nl; i++) x[i] = 0.0;

   vector<double> oldx(Nl);

   vector<double> BufferS(2 * nll * nlc);
   vector<double> BufferR(2 * nll * nlc);
   vector<MPI_Request> requestS(4), requestR(4);
   vector<MPI_Status> statusS(4), statusR(4);

   int iter = 0;
   double error = 1.0;

   //  ofstream os("toto_"+std::to_string(rank)+".txt");

   while (error > epsilon && iter < max_iter)
   {
      //    cout << "iter= " << iter << " error= " << error << endl;
      /*
      for (int i = 0; i < Nl; i++)
      {
         oldx[i] = x[i];
      }
      */
      updateX(Nl, x.data(), oldx.data());

      /*
      for (int i = 1; i < nll2 - 1; i++)
      {
         for (int j = 1; j < nlc2 - 1; j++)
         {
            int p = i * nlc2 + j;
            x[p] = 0.25 * (h2 * f[p] + (oldx[p + 1] + oldx[p - 1] + oldx[p + nlc2] + oldx[p - nlc2]));
         }
      }
      */
      Comput(nll2, nlc2, &(x[0]), &(oldx[0]), h2, &(f[0]));
      /*
          for(int k=0;k<nl2;k++)
          {
            for(int l=0;l<nl2;l++)
               os << x[k*nl2+l] << " ";
            os << endl;
          }
          os << endl;
      */
      array<int, 4> BTLR_size = {nlc, nlc, nll, nll};
      array<int, 5> BTLR_pos;
      BTLR_pos[0] = 0;
      for (int i = 0; i < 4; i++) BTLR_pos[i + 1] = BTLR_pos[i] + BTLR_size[i];

      /*
      for (int i = 0; i < nlc; i++)

      {
         BufferS[0 * nlc + i] = x[nlc2 + 1 + i];
         BufferS[1 * nlc + i] = x[(nll2 - 2) * nlc2 + 1 + i];
      }
      for (int i = 0; i < nll; i++)
      {
         BufferS[2 * nlc + i] = x[(i + 1) * nlc2 + 1];
         BufferS[2 * nlc + nll + i] = x[(i + 1) * nlc2 + nlc2 - 2];
      }
      */
      bufComput(nlc, nlc2, nll, nll2, &(x[0]), BufferS.data());

      /*
          for(int i=0;i<BufferS.size();i++)
            os << BufferS[i] << " " ;
          os << " BufferS " << rank << endl;
          os << endl;
      */

      for (int i = 0; i < 4; i++)
      {
         if (BTLR_rank[i] != -1)
            MPI_Irecv(&(BufferR[BTLR_pos[i]]), BTLR_size[i], MPI_DOUBLE, BTLR_rank[i], 123, MPI_COMM_WORLD, &(requestR[i]));
      }

      for (int i = 0; i < 4; i++)
      {
         if (BTLR_rank[i] != -1)
            MPI_Isend(&(BufferS[BTLR_pos[i]]), BTLR_size[i], MPI_DOUBLE, BTLR_rank[i], 123, MPI_COMM_WORLD, &(requestS[i]));
      }

      for (int i = 0; i < 4; i++)
      {
         if (BTLR_rank[i] != -1) MPI_Wait(&(requestR[i]), &(statusR[i]));
      }
      /*
          for(int i=0;i<BufferR.size();i++)
            os << BufferR[i] << " " ;
          os << " BufferR " << rank << endl;
          os << endl;
      */
      /*
      if (BTLR_rank[0] != -1)
         for (int i = 0; i < nlc; i++) x[0 * nlc2 + 1 + i] = BufferR[0 * nlc + i];
      if (BTLR_rank[1] != -1)
         for (int i = 0; i < nlc; i++) x[(nll2 - 1) * nlc2 + 1 + i] = BufferR[1 * nlc + i];
      if (BTLR_rank[2] != -1)
         for (int i = 0; i < nll; i++) x[(i + 1) * nlc2 + 0] = BufferR[2 * nlc + i];
      if (BTLR_rank[3] != -1)
         for (int i = 0; i < nll; i++) x[(i + 1) * nlc2 + nlc2 - 1] = BufferR[2 * nlc + nll + i];
         */
      bndUpdate(nlc, nlc2, nll, nll2, x.data(), BufferR.data(), BTLR_rank.data());

      /*
      double error_loc = 0.0;
      for (int i = 1; i < nll2 - 1; i++)
      {
         for (int j = 1; j < nlc2 - 1; j++)
         {
            int p = i * nlc2 + j;
            error_loc += pow(x[p] - oldx[p], 2.0);
         }
      }
      MPI_Allreduce(&error_loc, &error, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
      error = sqrt(error);
      */
      error = errorComput(nll2, nlc2, &(x[0]), &(oldx[0]));

      for (int i = 0; i < 4; i++)
      {
         if (BTLR_rank[i] != -1) MPI_Wait(&(requestS[i]), &(statusS[i]));
      }

      //    cout << error << endl;
      iter++;

      /*
          for(int k=0;k<nl2;k++)
          {
            for(int l=0;l<nl2;l++)
               os << x[k*nl2+l] << " ";
            os << endl;
          }
          os << endl;
      */
   }

   b = MPI_Wtime();

   array<int, 2> centerX;
   array<int, 2> centerC;
   centerC[0] = ncl / 2;
   if (ncl % 2 == 1)
      centerX[0] = nll2 / 2;
   else
      centerX[0] = 1;

   centerC[1] = ncc / 2;
   if (ncc % 2 == 1)
      centerX[1] = nlc2 / 2;
   else
      centerX[1] = 1;

   if (rank == centerC[0] * ncc + centerC[1])
   {
      cout << rank << " " << centerX[0] << " " << centerX[1] << endl;
      cout << "iter= " << iter << " error= " << error << " val= " << x[centerX[0] * nlc2 + centerX[1]] << " in " << b - a << " s"
           << endl;
   }

   //  write_vtk(rank,nl2,h,x,"toto_mpi");
   //  write_vti(rank,size,ncl,ncc,nll2,nlc2,h,x,"toto_mpi");

   MPI_Finalize();
   return 0;
}
