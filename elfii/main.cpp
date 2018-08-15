#include <fstream>
using namespace std;
ifstream f("elfi.in");
ofstream g("elfi.out");
int j,v[14401],n,c,p,t,i,nr;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>c>>p;
        t=2*c+p+1;
        for(j=t;j<=14400;j+=t)
        {
            v[j]++;
        }
    }
    for(i=1;i<=14400;i++)
    {
        if(nr<v[i])
            nr=v[i];
    }
    g<<nr;
    return 0;
}
