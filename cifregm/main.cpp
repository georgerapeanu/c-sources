#include <fstream>
#include <iostream>
using namespace std;
ifstream f("cifre.in");
ofstream g("cifre.out");
int main()
{
    long long cn,n,a[10],div=0,contor=0,b,d=0,e=0,nrcd=1,nrcd2=0,i;
    int uc;
    f>>n;
    cn=n;
    while(cn!=0)
    {
        uc=cn%10;
        cn=cn/10;
        d=d*10+uc;
    }
    for(i=1;i<=n;i++)
        if(n%i==0)
        div++;
    d=d+div;
    e=d;
    while(d!=0)
    {
       uc=d%10;
       d=d/10;
       nrcd*=10;
       nrcd2++;
    }
    nrcd/=10;
    for(i=1;i<=nrcd2;i++)
    {
        a[contor]=e/nrcd;
        e=e%nrcd;
        nrcd=nrcd/10;
        contor++;
    }
    contor--;
    b=contor/2;
    if(contor%2==1)
    {
        if(a[b]!=0)
        {
                g<<a[b]<<a[b+1];
        }
        else
        {
                g<<a[b+1];
        }
    }
    else
    {
        g<<a[b];
    }
    f.close();g.close();
    return 0;
}
