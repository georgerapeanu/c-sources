#include <fstream>
using namespace std;
ifstream f("nrpomi.in");
ofstream g("nrpomi.out");
int n,t,v[1001],i,p=1;
int main()
{
    f>>n>>t;
    for(i=0;i<n;i++)
        f>>v[i];
    for(i=1;i<n;i+=2)
    {
        if(i+1==n)
            p=p*(t-1);
        else if(v[i-1]!=v[i+1])
            p=p*(t-2);
        else
        p=p*(t-1);
           p=p%1234;
    }
    g<<p;
    return 0;
}
