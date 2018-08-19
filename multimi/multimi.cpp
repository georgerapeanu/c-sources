#include<iostream>
#include<fstream>
using namespace std;
ifstream f("multimi.in");
ofstream g("multimi.out");
int main()
{
    int a,n,b,i,maxi=0,mini=30000,c,j=0;
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a>>b;
            if(a>c)
            {
                i=n+1;j=1;
            }
          else
          {
        if(a>maxi)
            maxi=a;
        if(b<mini)
            mini=b;
            c=b;
          }
    }
    if(j==0)
    {
    for(i=maxi;i<=mini;i++)
    {
        g<<i<<" ";
    }
    }
    else
    {
        g<<"multimea vida";
    }
    f.close();g.close();
    return 0;
}
