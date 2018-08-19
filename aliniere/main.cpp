#include <fstream>
#define MOD 9973
using namespace std;
ifstream f("aliniere.in");
ofstream g("aliniere.out");
int x,y,z,N;
int main()
{
    f>>N;
    x=1;
    y=2;
    z=3;
    if(N==1)
        g<<1;
    else if(N==2)
        g<<2;
    while(N>3)
    {
        N--;
        x=y;
        y=z;
        z=(x+y)%MOD;
    }
    g<<z;
    f.close();
    g.close();
    return 0;
}
