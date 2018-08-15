#include <fstream>
#include <math.h>
using namespace std;
ifstream f("cartier.in");
ofstream g("cartier.out");
long n,h[100001],l[100001],i,j,a,maxh,nrh,sl,c,gasit,maxc;
int cmmdc(int a1,int b)
{
if(a1==b) return a1;
else
if (a1>b) return cmmdc(a1-b,b);
else return cmmdc(a1,b-a1);
}
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        for(j=int(sqrt(a));j>=1;j--)
        {
            if(a%j==0)
            {
                l[i]=j;h[i]=a/j;break;
            }
        }
        if(h[i]>maxh)
        {maxh=h[i];nrh=1;}
       else  if(h[i]==maxh)
        nrh++;
        sl+=l[i];
    }
    for(i=1;i<=n;i++)
    {
        for(j=n;j>i;j--)
        {
            if(cmmdc(h[i],h[j])!=1)
            {
                c=j-i+1;break;
            }
        }
        if(c>maxc)
        maxc=c;
    }
    g<<nrh<<"\n"<<sl<<'\n'<<maxc;
    f.close();g.close();
    return 0;
}
