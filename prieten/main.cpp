#include <fstream>
using namespace std;
ifstream f("prieten.in");
ofstream g("prieten.out");
long long N,K,S,i;
int main()
{
    f>>N>>K>>S;
    for(i=1;i<=K;i++)
        g<<i*(N+1)<<" ";
    g<<"\n";
    i=1;
    while(i*(i+1)*(i+2)/2!=S)
    {
        i++;
    }
    g<<i+1;
    f.close();
    g.close();
    return 0;
}
