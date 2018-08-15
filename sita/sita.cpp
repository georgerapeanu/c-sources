#include<fstream>
using namespace std;
ifstream f("sita.in");
ofstream g("sita.out");
int main()
{
    long nr,k,l,d,i,j=1,s,c,p=1,a,b,e;
    f>>nr>>k;
    l=3*nr+1;
    d=2*nr+1;
    g<<l<<" ";
    for(i=1;i<=4;i++)
    {
        l=l+d;
        g<<l<<" ";
    }
    g<<endl;
   s=3*j+1;
   c=2*p+1;
    while(s!=k)
    {
        if(s>k)
        {
            p++;
            j++;
            s=3*j+1;
            c=2*p+1;
        }
        s=s+c;
    }
    if(p==j)
    {
        a=s+c;
        g<<a;
    }
    else
    {
        a=s+c;
        e=p*2+1;
        b=d+e;
        if(a>b)
            g<<b;
        else
            g<<a;
    }
    f.close();g.close();
    return 0;
}
