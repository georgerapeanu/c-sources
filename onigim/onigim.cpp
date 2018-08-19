#include<iostream>
#include<fstream>
using namespace std;
ifstream f("onigim.in");
ofstream g("onigim.out");
int main()
{
    int i,n,k,b,l=0,j,gasit,nrb=0;
    f>>n>>k;
    int p[k],a[n],v[n];
    for(i=0;i<k;i++)
    {
        f>>p[i];
    }
     for(i=0;i<n;i++)
    {
        f>>a[i];
    }
   for(i=0;i<n;i++)
   {
       gasit=0;
       for(j=0;j<n;j++)
       {
           if(a[j]==i)
            {
            gasit=1;
            v[j]=p[l];
            }
       }
       if(gasit==1)
       {
           l++;
       }
   }
   for(i=0;i<n;i++)
   {
       g<<v[i]<<" ";
   }
   int y=0,s[3]={p[k-1],p[k-2],p[k-3]};
   for(j=0;j<3;j++)
   {
       for(i=0;i<n;i++)
       {
           if(v[i]==s[j])
            nrb++;
       }
   }
   g<<"\n"<<nrb<<"\n";
   int maxc=0,nrc=0;
   for(i=0;i<n;i++)
   {
       nrc=0;
       for(j=0;j<n;j++)
       {
           if(v[i]==v[j])
            nrc++;
       }
       if(maxc<nrc)
        maxc=nrc;
   }
   g<<maxc;
    f.close();g.close();
    return 0;
}
