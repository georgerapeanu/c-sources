#include <fstream>
#include <math.h>
using namespace std;
ifstream f("cepe.in");
ofstream g("cepe.out");
long long r,a,b,a1[15],b1[15],nr,nr2,nrc2,nrc,temp,i,j;
int main()
{
    f>>a>>b;
    while(a!=0)
    {
       r=a%2;
       a=a/2;
       a1[nr]=r;
       nr++;
    }
    nr--;
       while(b!=0)
    {
       r=b%2;
       b=b/2;
       b1[nr2]=r;
       nr2++;
    }
    nr2--;
    for(i=0;i<=nr/2;i++)
    {
        temp=a1[i];
        a1[i]=a1[nr-i];
        a1[nr-i]=temp;
    }
    for(i=0;i<=nr2/2;i++)
    {
        temp=b1[i];
        b1[i]=b1[nr2-i];
        b1[nr2-i]=temp;
    }
    j=0;
    nrc=nr;
    nrc2=nr2;
   while(j<=nrc&&nrc2>=0&&a1[j]==b1[nrc2])
    {
     j++;nrc2--;
    }
    for(i=j;i<=nr;i++)
    {
        if(a1[i]==1)
        a=a+pow(2,nrc-i);
    }
    for(i=0;i<=nrc2;i++)
    {
        if(b1[i]==1)
        b=b+pow(2,nrc2-i);
    }
    g<<(a+b);
    f.close();
    return 0;
}
