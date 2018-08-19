#include<iostream>
#include<fstream>
using namespace std;
ifstream f("divizor.in");
ofstream g("divizor.out");
int main()
{
    int n,m=1,l,i,d=1,j,maxd=0,k=0,maxdiv=0,maxl=0,r[m-1],div[m-1];
    f>>n;
    l=n;
    while(l>9)
    {
        m++;l=l/10;
        d=d*10;
    }
    for(i=1;i<=m;i++)
    {
        r[i-1]=n;cout<<r[i-1]<<endl;
        if(n/d!=0)
        {
        n=n/d+n%d*10;
        }
        else n=n*10;
        k=0;
        for(j=2;j<=r[i-1]/2;j++)
        {
            if(r[i-1]%j==0)
                k++;
        }
        div[i-1]=k;
        if(k>maxd)
        {
            maxd=k;
        }
    }
    for(i=1;i<=m;i++)
    {
        if(div[i-1]==maxd) g<<r[i-1]<<" ";
    }
    for(i=1;i<=m;i++)
    {
    for(j=(r[i-1]/2);j>=2;j--)
   {
       if(r[i-1]%j==0)
       {
           maxdiv=j;
           j=1;
       }
   }
    }
   g<<endl<<maxdiv;
   f.close();g.close();
   return 0;
}
