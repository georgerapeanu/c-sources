#include <fstream>
#include <cmath>
using namespace std;
ifstream f("fact.in");
ofstream g("fact.out");
unsigned long long nr=1,nr1=1;
int n,k,i;
bool gasit=0;
short nr2;
int main()
{
    f>>n>>k;
    for(i=1;i<=n;i++)
    {
        f>>nr2;
        nr*=nr2;
    }
    i=2;
    while(i<=k)
    {
        if(nr1%nr==0)
        {
            gasit=1;
            break;
        }
        nr1*=i;
        i++;
    }
     if(nr1%nr==0)
        {
            gasit=1;
        }
    if(gasit==0)
    g<<"NU";
    else
    g<<"DA";
    return 0;
}
