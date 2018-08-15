#include <fstream>
using namespace std;
ifstream f("np.in");
ofstream g("np.out");
bool repr2[1000];
int n;
long long rez,pow3=1;
int nrcifre,i;
int main()
{
    f>>n;
    while(n)
    {
        repr2[++nrcifre]=n&1;
        n=n>>1;
    }
    for(i=1;i<=nrcifre;i++)
    {
        rez+=pow3*repr2[i];
        pow3*=3;
    }
    g<<rez;
    f.close();
    g.close();
    return 0;
}
