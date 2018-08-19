#include <fstream>
using namespace std;
ifstream f("sir.in");
ofstream g("sir.out");
long n;
unsigned long long a,b,dif,i,nr,cmmdc,nrdiv=1,ca,r;
bool rost=1;
int main()
{
    f>>n;
    f>>a;i=3;b=a;f>>a;
        if(b>a)
        {
            rost=0;
        }
        cmmdc=a-b;
        if(rost==1)
    while(i<=n)
    {
        f>>a;
        if(b<a)
        {
            dif=a-b;
            r=dif%cmmdc;
            while(r!=0)
            {
                dif=cmmdc;cmmdc=r;r=dif%cmmdc;
            }
        }
        else
        {
            rost=0;break;
        }
        i++;
        b=a;
    }
    if(rost==0)
    g<<0;
    else
    {
        unsigned long long j=2;
       while(cmmdc!=1)
       {
           nr=0;
               while(cmmdc%j==0)
               {
                   nr++;cmmdc/=j;
               }
               j++;
              nrdiv*=(nr+1);
       }

    g<<nrdiv;
    }
    f.close();g.close();
    return 0;
}
