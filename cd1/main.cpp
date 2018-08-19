#include <fstream>
#include <iostream>
using namespace std;
ifstream f("cd1.in");
ofstream g("cd1.out");
long long int s,n,y[301],x[301],c[301],i,p=1,k,j;
int main()
{
    f>>n>>s;
    for(i=1;i<=n;i++)
    {
        f>>y[i]>>c[i];
        x[i]=x[i]+s/n+y[i];
        x[c[i]]=x[c[i]]-y[i];
    }
    for(i=1;i<=n;i++)
    {
    p=p*(x[i]-1)%9901;
    }
    g<<p;
    f.close();g.close();
    return 0;
}
