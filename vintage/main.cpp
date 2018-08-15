#include<fstream>
#include<algorithm>
#include<iostream>
using namespace std;
ifstream f("vintage.in");
ofstream g("vintage.out");
long long n,m,i,p,vmax,nrmaxim,cost,cmin,c[1000],x,j,a[1000],b[1000];
int main()
{
    f>>n>>m;
    for(i=0;i<n;i++)
    {
        f>>a[i]>>b[i];
    }
    for(j=0;j<m;j++)
    {
        nrmaxim=0;cost=0;
   for(i=0;i<n;i++)
   {
       if(b[i]==nrmaxim)
       {
           if(a[i]<cost)
           {
            cost=a[i];
            p=i;
           }
       }
       if(b[i]>nrmaxim)
       {
           nrmaxim=b[i];
           cost=a[i];
           p=i;
       }
   }
   c[x]=p+1;
   x++;
   vmax+=nrmaxim;
   cmin+=cost;
   b[p]=0;
   a[p]=0;
    }
    g<<vmax<<" "<<cmin<<"\n";
    sort(c,c+x);
    for(i=0;i<x;i++)
        g<<c[i]<<" ";
   f.close();g.close();
   return 0;
   }
