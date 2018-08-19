#include <fstream>
using namespace std;
ifstream f("input.in");
ofstream g("output.out");
long long a,i;
double m,s,n;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
       f>>a;
       s+=a;
    }
    m=s/n*1.0;
   g<<int(m)<<'.';
   m=m-int(m);
   m=m*100;
   g<<int(m);
    return 0;
}
