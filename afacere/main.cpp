#include <fstream>
using namespace std;
ifstream f("afacere.in");
ofstream g("afacere.out");
long s,n,a,i,nr;
int main()
{
    f>>s>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(a>s)
        {
          nr+=a-s;g<<s<<"\n";
        }
        else
        g<<a<<"\n";
    }
    g<<nr;
    return 0;
}
