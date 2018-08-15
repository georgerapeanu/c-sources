#include<iostream>
#include<fstream>
using namespace std;
ifstream f("rude.in");
ofstream g("rude.out");
int main()
{
    int m=0,n,a,d,k,z=1,r,p,l,c,x=0,b,maxim=0;
    f>>n;
    l=n;
    while(n!=0)
    {
        n=n/10;
        m++;
        z=z*10;
    }
    z=z/10;
    a=l/z;
    r=l%z;
    for(d=1;d<=m-1;d++)
    {
        z=z/10;
        k=r/z;
        p=k*z*10+a*z+r%z;
        if(p>maxim)
            maxim=p;
        }
        while(r!=0)
        {
            b=r%10;
            r=r/10;
            if(b==a)
                x++;
        }
    m=m-1;
    g<<m<<endl;
    m=m-x;
    g<<m<<endl;
    g<<maxim;

}
