#include <fstream>
using namespace std;
ifstream f("ucif.in");
ofstream g("ucif.out");
int i,n,us,up,j;
int main()
{
    f>>n;
for(i=1;i<=n;i++)
{
 up=1;
 for(j=1;j<=i;j++)
  up=(up*i)%10;
 us  =(us+up)%10;
}
g<<us;
    return 0;
}
