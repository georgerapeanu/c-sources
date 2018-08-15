#include <fstream>
using namespace std;
ifstream f("grupe.in");
ofstream g("grupe.out");
int n,i;
long long tmp,a,b;
int main()
{
    a=1;
    b=1;
    i=1;
    f>>n;
    while(i<=n)
    {
        tmp=b;
        b=b+a;
        a=tmp;
        i++;
    }
    g<<b-1;
    f.close();
    g.close();
    return 0;
}
