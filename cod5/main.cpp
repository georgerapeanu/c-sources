#include<fstream>
using namespace std;
ifstream f("cod5.in");
ofstream g("cod5.out");
long i,a,n;
bool v[90001];
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        v[a]^=1;
    }
    for(i=0;i<=99;i++)
    {
        if(v[i]!=0)
            g<<i;
    }
    f.close();g.close();
    return 0;
}
