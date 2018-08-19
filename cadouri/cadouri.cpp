#include<fstream>
using namespace std;
ifstream f("cadouri.in");
ofstream g("cadouri.out");
int main()
{
    int i,b,fe,n,a,cb=0,cf=0;
    f>>fe>>b>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(a%2==0)
            cf++;
        else
            cb++;
    }
    if(cf>=fe)
        g<<0<<"\n";
    else
        g<<(fe-cf)<<"\n";
    if(cb>=b)
        g<<0;
    else
        g<<(b-cb);
        f.close();g.close();
    return 0;
}
