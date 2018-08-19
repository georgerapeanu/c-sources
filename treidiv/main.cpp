#include <fstream>
#include <math.h>
using namespace std;
ifstream f("treidiv.in");
ofstream g("treidiv.out");
long long ciur[1001],a,i,nr,j,n;
int main()
{
    f>>n;ciur[0]=ciur[1]=1;
    for(i=2;i<=1000&&ciur[i]!=1;i++)
    {
        for(j=i*i;j<=1000;j+=i)
        {
            ciur[j]=1;
        }
    }
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(sqrt(a)==int(sqrt(a)))
        {
            if(ciur[int(sqrt(a))]==0)
            nr++;
        }
    }
    g<<nr;
    f.close();
    g.close();
    return 0;
}
