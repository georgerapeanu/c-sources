#include<fstream>
using namespace std;
ifstream f("danut.in");
ofstream g("danut.out");
int main()
{
  int k=1,n,a,b,j,i;
  f>>n;
  while(k*k<=n)  k++;
  a=1;b=n;
  for(i=2;i<=k;i++)
  {
      j=n/i;
      if(i*j<n)
        j++;
      if(i+j<a+b)
   {
        a=i;
        b=j;
   }
  }
  g<<a<<" "<<b;
  f.close();g.close();
  return 0;
}
