#include <fstream>
#include <cmath>
#define x first
#define y second
using namespace std;
ifstream f("qtri.in");
ofstream g("qtri.out");
typedef pair<int,int> point;
point a,b,c,d;
int T;
int arie(point a,point b,point c)
{
    return abs(a.x*b.y+b.x*c.y+c.x*a.y-b.x*a.y-c.x*b.y-a.x*c.y);
}
int main()
{

    f>>T;
    while(T)
    {
        f>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y>>d.x>>d.y;
        if(arie(a,b,d)+arie(b,c,d)+arie(c,a,d)==arie(a,b,c))
            g<<"DA\n";
        else
            g<<"NU\n";
        T--;
    }
    return 0;
}
