#include <fstream>
using namespace std;
ifstream f("set.in");
ofstream g("set.out");
int n;
long long prim,ultim;
int main()
{
    f>>n;
    ultim=n*(n+1)-2;
    prim=n*(n-1);
    if(((ultim-prim)/2+1)%2==0)
    {
        g<<prim<<"\n"<<(ultim+prim)*(((ultim-prim)/2+1)/2);
    }
    else
    {
        g<<prim<<"\n"<<(ultim+prim)*(((ultim-prim)/2+1)/2)+(ultim+prim)/2;
    }
    f.close();
    g.close();
    return 0;
}
