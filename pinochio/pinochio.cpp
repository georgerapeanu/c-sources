#include<fstream>
using namespace std;
ifstream f("pinochio.in");
ofstream g("pinochio.out");
int main()
{
    int n,p,k,c,r,cm;
    f>>n>>p>>k;
    c=k/7;
    r=k%7;
    cm=n+c*5*p-c*2;
    if(r<=5)
        cm=cm+r*p;
    else
    {
        if(r==6)
            {
                cm=cm+5*p-1;
            }
            if(r==0)
            {
                cm=cm+5*p-2;
            }

    }
    g<<cm;
    f.close();g.close();
    return 0;
}
