#include<fstream>
ifstream f("ingerasi.in");
ofstream g("ingerasi.out");
using namespace std;
int main()
{
    long k=0,n,i,mini,l=0,m;
    f>>n;
    int v[n];
    for(i=0;i<n;i++)
    {
        f>>v[i];
    }
    mini=v[0];
    while(k==0)
 {
    for(i=0;i<n;i++)
    {
        if(v[i]<mini)
        {
            m=i;
            mini=v[i];
        }
    }
    for(i=0;i<n;i++)
    {
        if(i!=m)
        {
            v[i]=v[i]-v[m];
        }
    }
    for(i=1;i<n;i++)
    {
        if(v[i]==v[i-1])
            k=1;
        else
        {
            k=0;
            i=n;
        }
    }
}
g<<v[0];
    return 0;
}
