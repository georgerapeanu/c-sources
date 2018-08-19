#include <fstream>
#include <stdlib.h>
using namespace std;
ifstream f("cai.in");
ofstream go("cai.out");
long p[10001],g[10001],i,n,m,j,nr;
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>p[i];
    }
    f>>m;
    for(i=1;i<=m;i++)
    {
        f>>g[i];
    }
    qsort (p, n, sizeof(long), compare);
    qsort (g, m, sizeof(long), compare);
    for(i=1;i<=m;i++)
    {
        while(p[i+j]<g[i])
        {
            j++;
            if(i+j>n)
            break;
        }
        if(p[i+j]>=g[i])
        nr++;
    }
    go<<nr;
    return 0;
}
