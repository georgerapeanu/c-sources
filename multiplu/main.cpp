#include <fstream>
#include <cmath>
using namespace std;
ifstream f("multiplu.in");
ofstream g("multiplu.out");
long i=2,n,coo=0,maxim,putere,nr,nr2;
int main()
{
    f>>n;
    while(n!=1)
    {
        if(n%i==0)
        {
           putere=0;
           while(n%i==0)
           {
               n/=i;putere++;
           }
           nr=1;
           while(putere>nr)
           {
               putere-=nr;
               nr++;
           }
           nr2=pow(i,nr);
           if(nr2>maxim)
           maxim=nr2;
        }
        i++;
    }
    g<<maxim;
    return 0;
}
