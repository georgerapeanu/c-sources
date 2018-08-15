#include<iostream>
#include<fstream>
using namespace std;
ifstream f("extraprime.in");
ofstream g("extraprime.out");
int prim(int x)
{
    if(x<2) return 0;
    else
    {
        for(int i=2;i<=x/2;i++)
        {
            if(x%i==0) return 0;
        }
    }
    return 1;
}
int main()
{
    long a,b,i,ca=0,cb=0,d,c,l=1,k=1,v,z,t,y,q,w,s,p=0;
    f>>a>>b;
    c=a;
    d=b;
    while(c)
    {
        ca++;
        c=c/10;
        l*=10;
    }
    while(d)
    {
        cb++;
        d=d/10;
        k*=10;
    }
    l/=10;k/=10;
    if(ca==cb)
    {
    for(i=a;i<=b;i++)
    {
        d=l;
        p=0;
        for(i=1;i<=ca;i++)
        {
        v=i/d;
        s=i%d;
        q=i%d*10/d;
        w=q*d+s;
        if(prim(w)) p=1;
        d=d/10;
        }
        if(p==1)
            g<<i<<" ";
    }
    }
    f.close();g.close();
    return 0;
}
