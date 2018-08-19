#include<fstream>
using namespace std;
ifstream f("tort.in");
ofstream g("tort.out");
int main()
{
    int m,n,t,r;
    f>>m>>n;
    t=m*n;
    r=m%n;
    while(r!=0)
    {
        m=n;
        n=r;
        r=m%n;
    }
    g<<(t/n/n)<<" "<<n;
    f.close();g.close();
    return 0;
}
