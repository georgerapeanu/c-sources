#include <fstream>
#include <cmath>
using namespace std;
ifstream f("tablita.in");
ofstream g("tablita.out");
long long n,st,dr,lung;
int main()
{
    f>>n;
    f.close();
    lung=sqrt(double(n));
    st=lung*(lung-1)/2+1;
    dr=st+lung-1;
    while(!(st<=n&&n<=dr))
    {
        st=dr+1;
        lung++;
        dr=st+lung-1;
    }
    g<<lung;
    g.close();
    return 0;
}
