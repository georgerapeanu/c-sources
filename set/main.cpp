#include <fstream>
using namespace std;
ifstream f("set.in");
ofstream g("set.out");
unsigned long long n,s,i,u,p;
int main()
{
    f>>n;
    p=n*(n-1);
    u=p+2*(n-1);
    i=(u-p)/2+1;
    s=i*p+(i-1)*i;
    g<<p<<"\n"<<s;
    f.close();g.close();
    return 0;
}
