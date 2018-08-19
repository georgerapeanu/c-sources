#include <fstream>
using namespace std;
ifstream f("atelier.in");
ofstream g("atelier.out");
long i,n,sa[10001],sb[10001],a,b,maxim,imax,gasit;
char poz;
int main()
{

   f>>n;
   sa[0]=0;sb[0]=0;
   for(i=1;i<=n;i++)
      {
          f>>a>>b;
          sa[i]=sa[i-1]+a;sb[i]=sb[i-1]+b;
      }
   maxim=sa[1]+(sb[n]-sb[1]);imax=1;poz='A';
   for(i=2;i<=n-1;i++)
   {
       if((sa[i]+(sb[n]-sb[i]))>maxim)
             {maxim=sa[i]+(sb[n]-sb[i]);imax=i;}
   }
  for(i=2;i<=n-1;i++)
{
        if((sb[i]+(sa[n]-sa[i]))>maxim)
            {maxim=sb[i]+(sa[n]-sa[i]);imax=i;poz='B';}
}
g<<maxim<<"\n"<<poz<<"\n"<<imax;
f.close();g.close();
return 0;
}
