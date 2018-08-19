#include <fstream>
using namespace std;
ifstream f("numere.in");
ofstream g("numere.out");
long long c,minim=1000000,k,m,n,i,a[1001],b[1001],nr,j;
int main()
{
    f>>n>>m;
    for(i=1;i<=n;i++)
    {
        f>>a[i];
    }
    for(i=1;i<=m;i++)
    {
        f>>b[i];
        minim=minim>b[i] ? b[i]:minim;
    }
    for(i=1;i<=n;i++)
    {
        if(a[i]>=minim)
        {
            for(j=1;j<=m;j++)
            {
                c=a[i];k=j;
                while(c>=b[j]&&k<=m)
                c-=b[k++];
                if(c==0)
                {
                    nr++;break;
                }
            }
        }
    }
    g<<nr;
    return 0;
}
