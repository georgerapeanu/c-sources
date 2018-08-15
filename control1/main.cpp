#include <fstream>
using namespace std;
ifstream f("control1.in");
ofstream g("control1.out");
long long a,b,c1,c2,r1,r2;
int c;
int main()
{
    f>>a>>b>>c;
    f.close();
    c1=a/9;r1=a%9;
    c2=b/9;r2=b%9;
    if(r1>c)
        c1++;
    if(r2<c);
        c2--;
    g<<(c2-c1+1 >0 ? c2-c1+1:0);
    g.close();
    return 0;
}
