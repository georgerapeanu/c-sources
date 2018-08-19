#include <fstream>
using namespace std;
ifstream f("majoritar.in");
ofstream g("majoritar.out");
unsigned long int a,maxim,n,i,nrmax,maxnr;
unsigned long long int v[100000001];
int main()
{
     f>>n;
     for(i=1;i<=n;i++)
     {
         f>>a;
         v[a]++;
         maxim=(maxim>a ? maxim:a);
     }
     for(i=0;i<=maxim;i++)
     {
        if(v[i]>maxnr)
        {
             nrmax=i;maxnr=v[i];
        }
     }
     if(maxnr>n/2)
     g<<nrmax<<" "<<maxnr;
     else
     g<<-1;
     f.close();g.close();
    return 0;
}
