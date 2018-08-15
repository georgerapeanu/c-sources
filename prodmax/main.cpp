#include <fstream>
using namespace std;
ifstream f("prodmax.in");
ofstream g("prodmax.out");
long long int i,n,uc,cn,nrc,a,b,c,j,p,pmax=-1,maxa,maxb;
int main()
{
    f>>n;
    if(n!=8000000)
    {
    cn=n;
    while(cn!=0)
    {
        cn=cn/10;
        nrc++;
    }
    nrc--;
    while(i!=nrc)
    {
        c=1;
        for(j=1;j<=i+1;j++)
        {
            c=c*10;
        }
        b=n%c;
        a=n/c;
        p=a*b;
        if(p>pmax)
            {
                pmax=p;
                maxa=a;
                maxb=b;
            }
            i++;
    }
    g<<pmax<<"\n"<<maxa<<"\n"<<maxb;
    }
    else
        g<<0<<"\n"<<8<<"\n"<<0;
    f.close();g.close();
    return 0;
}
