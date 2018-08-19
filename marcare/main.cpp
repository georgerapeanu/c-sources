#include <fstream>
using namespace std;
ifstream f("marcare.in");
ofstream g("marcare.out");
int n,k,s,v[255],i,nr;
int main()
{
    f>>n>>s>>k;
    i=s-1;
    while(v[i]!=2)
   {
       v[i]++;
       if(v[i]==1)
       {
        g<<(i+1)<<" ";nr++;
       }
       i+=k;
       if(i>=n)
       {
           i=i-n;
       }
   }
   g<<"\n"<<(n-nr);
    return 0;
}
