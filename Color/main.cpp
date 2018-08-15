#include <fstream>
using namespace std;
ifstream f("color.in");
ofstream g("color.out");
int N,M;
int gr[4005];
long long rez,scad;
int main()
{
    f>>N>>M;
    rez=(1LL*N*(N-1)*(N-2))/6;
    for(int i=1;i<=M;i++)
    {
        int a,b;
        f>>a>>b;
        gr[a]++;
        gr[b]++;
    }
    for(int i=1;i<=N;i++)
    {
        scad+=1LL*(gr[i])*(N-1-gr[i]);
    }
    g<<rez-scad/2;
    return 0;
}
