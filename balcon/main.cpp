#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("balcon.in");
ofstream g("balcon.out");
int a[51][51],v[2500],x,n,i,j,k;
int main()
{
    f>>n;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        f>>v[i*n+j];
    sort(v,v+n*n);
    x=0;
    for(k=1;k<=(n+1)/2;k++)
    {
        for(j=k;j<=n+1-k;j++)
        {
            a[k][j]=v[x];
            x++;
        }
        for(i=k+1;i<=n-k+1;i++)
        {a[i][n-k+1]=v[x];x++;}
        for(j=n-k;j>=k;j--)
        {a[n-k+1][j]=v[x];x++;}
        for(i=n-k;i>k;i--)
        {a[i][k]=v[x];x++;}
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        g<<a[i][j]<<" ";
        g<<"\n";
    }
    return 0;
}
