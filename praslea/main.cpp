#include <fstream>
#include <stdlib.h>
using namespace std;
ifstream f("praslea.in");
ofstream g("praslea.out");
long v[10001],n,m,i,a,j,o[500001],dif,maxim,d,l,l1;
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main()
{
    f>>n>>m>>l;
    for(i=1;i<=m;i++)
    {
        f>>a>>l1;
        v[j]=a;j++;
        o[a]=l1;
    }
    f>>d;
    qsort(v,j,sizeof(long),compare);
    for(i=1;i<=j;i++)
    {
        dif=v[i]-v[i-1]-1;
        if(dif>maxim)
        maxim=dif;
    }
    dif=n-v[j-1];
    if(dif>maxim)
    maxim=dif;
    g<<maxim<<"\n";
    i=1;
    while(d>0)
    {
       if(o[i]==0)
       {
           o[i]=l;
       }
       d=d-o[i];
     i++;
    }
    g<<(i-1);
    return 0;
}





