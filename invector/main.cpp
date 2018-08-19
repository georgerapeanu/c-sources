#include <fstream>
using namespace std;
ifstream f("invector.in");
ofstream g("invector.out");
long long n,v[100005],i;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    f>>v[i];
    for(i=n;i>=1;i--)
    g<<v[i]<<" ";
    f.close();
    g.close();
    return 0;
}

