#include <fstream>
using namespace std;
long long pct,nrmax,nr,n=1,i;
short v[100000000];
ifstream f("schi.in");
ofstream g("schi.out");
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>pct;
        if(pct<=nrmax)
        nr++;
        else
        {
            v[nrmax]=nr;
            nrmax=pct;
            nr=1;
        }
    }
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>nr;
        g<<v[nr]<<" ";
    }
    f.close();
    g.close();
    return 0;
}
