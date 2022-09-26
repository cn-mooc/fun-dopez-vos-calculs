#include <iostream>
using namespace std;

int error1(int a)
{
   int f = 1;
   f=f/(a-1);
   return f;
}
int error2(int *p)
{
   int v = p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
   if (v > 2)
      return 1;
   else
      return 0;
}
int main(int argc, char **argv)
{
   int *d = new int[3];
   d[0] = d[2] = 1;
   // une erreur division entiere par 0
   int h = error1(d[0]);
   // une autre erreur de variable non initilise
   int g = error2(d);
   cout << "reading out of range " << d[3] << endl;
   cout << "writing out of range " << endl;
   d[3] = 5;
   // delete [] d;
}
