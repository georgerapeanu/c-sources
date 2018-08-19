#include <fstream>
using namespace std;
ifstream f("porumb.in");
ofstream g("porumb.out");
int i,n,m,s1,s2,s,a;
int main()
{
    f>>n>>m;
    for(i=1;i<=n;i++)
        {
            f>>a;
            s+=a;
        }
    s1=m-1;
    s2=n-m;
    if(s1<s2)
        s+=2*s1+s2;
    else
        s+=2*s2+s1;
        g<<s;
    f.close();g.close();
    return 0;
}
