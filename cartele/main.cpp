#include <fstream>
#include <iomanip>
#define DIM 51
using namespace std;
ifstream fin("cartele.in");
ofstream fout("cartele.out");

int a[DIM][DIM], b[DIM][DIM];  // sablonul, cartela
int aux[DIM][DIM];
int n, C;

int  Egale();
void Inverseaza();            // intoarce cartela pe partea cealalta (oglindire fata de linia i = n/2)
void Roteste();               // rotire 90 grade in sens trigonometric
void Rezolva();

int main()
{
   Rezolva();
   fin.close();
   fout.close();
   return 0;
}

void Rezolva()
{
   fin >> n >> C;
   int i, j, r;
   int identice = 1;
   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
 	 fin >> a[i][j];

   for (int k = 1; k <= C; k++)
      {
         identice = 1;
         for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
               {
                  fin >> b[i][j];
                  if ( b[i][j] != a[i][j] ) identice = 0;
               }

         for (int f = 1; f <= 2 && !identice; f++)  // pentru fata 1 si 2
            {
               for (r = 1; r <= 4 && !identice; r++)  // la a patra rotatie se revine la matricea initiala
                  {
                     Roteste();    // cu 90 in sens trigonometric
                     if ( Egale() ) identice = 1;
                  }
               if ( !identice ) Inverseaza();
            }
         if ( identice )
            fout << 1 << '\n';
         else
            fout << 0 << '\n';
      }
}

int Egale()
{
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         if ( a[i][j] != b[i][j] ) return 0;
   return 1;
}

void Inverseaza()
{
   int i, j, temp;
   for (i = 1; i <= n / 2; i++)
      for (j = 1; j <= n; j++)
         temp = b[i][j], b[i][j] = b[n-i+1][j], b[n-i+1][j] = temp;
}

void Roteste()
{
   int i, j;
   for (i = 1; i <= n; i++)
      for (j = 1; j<= n; j++)
         aux[n-j+1][i] = b[i][j];

   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
         b[i][j] = aux[i][j];
}
