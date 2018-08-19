#include <fstream>
using namespace std;
ifstream f("magicsequence.in");
ofstream g("magicsequence.out");
int T,N,a,b,i,j;
int main()
{
    f>>T;
    for(i=1;i<=T;i++)
    {
        f>>N;
        f>>a;
        for(j=2;j<=N;j++)
        {
            f>>b;
        }
        if(a<=b)
            g<<"YES\n";
        else
            g<<"NO\n";
    }
    f.close();
    g.close();
    return 0;
}
