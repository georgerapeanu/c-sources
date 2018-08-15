#include <fstream>
using namespace std;
ifstream f("greieri.in");
ofstream g("greieri.out");

int main()
{
    long long l,n,m,i,r,c,s=1,k,p;
    f>>n>>m;
    l=n*(n-1);
    g<<l<<"\n";
    m=m%l;
    r=m%(n-1);
    c=m/(n-1);
    k=n-r;
    p=n-c;
    for(i=n-c+1;i<=n;i++)
    {
        if(s==k) g<<p<<" ";
        g<<i<<" ";
        s++;
    }
    for(i=1;i<n-c;i++)
    {
        if(s==k) g<<p<<" ";
        g<<i<<" ";
        s++;
    }
    if(!r) g<<p;
    f.close();g.close();
}
