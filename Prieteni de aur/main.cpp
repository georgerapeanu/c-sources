#include <fstream>
using namespace std;
ifstream f("prieteni.in");
ofstream g("prieteni.out");
long long p1, p2, p3, p3c, maxi, n, i, maxcf, cf, prieteni;
int main()
{
  f>>n;
  prieteni = 0;
  for ( i = 0; i < n; i++ )
  {
    f>>p3;
    p1 = p2 = 0;
    while ( p3 > 9 && p3 != p1 )
    {
      p1 = p2;
      p2 = p3;
      maxi = maxcf = 0;
      p3c = p3;
      while ( p3c > 0 )
      {
        maxi = maxi * 10 + 1;
        cf = p3c % 10;
        p3c /= 10;
        if ( cf > maxcf )
          maxcf = cf;
      }
      p3 = maxi * maxcf - p3;
    }
    if ( p3 <= 9 && p3 > 0 )
      prieteni++;
  }
  g<<prieteni;
return 0;
}
