#include <fstream>
using namespace std;
ifstream f("zerouri.in");
ofstream g("zerouri.out");
unsigned long long a,b,nr5,nr2,div=5;
int main()
{
    f>>a>>b;
    while(b/div!=0)
    {
        nr5+=b/div;
        nr5-=a/div;
        div*=5;
    }
    div=2;
    while(b/div!=0)
    {
        nr2+=b/div;
        nr2-=a/div;
        div*=2;
    }
    if(nr5>nr2)
    g<<nr2;
    else
    g<<nr5;
    return 0;
}
