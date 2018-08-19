#include<fstream>
using namespace std;
ifstream f("subsecvmax.in");
ofstream g("subsecvmax.out");
long long i,n,lg,maxim=1,nr,felem,x,rezx=1;
int main()
{
    f>>n;
    f>>felem;
    lg=1;
    x=1;
    for(i=2;i<=n;i++)
    {
        f>>nr;
        if(felem<=nr)
        {
            lg++;
            felem=nr;
        }
        else
        {
            if(maxim<lg)
            {
                maxim=lg;
                rezx=x;
            }
            x=i;
            lg=1;
            felem=nr;
        }
    }
    g<<rezx<<" "<<maxim;
    f.close();
    g.close();
    return 0;
}
