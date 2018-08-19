#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("rucsac1.in");
ofstream g("rucsac1.out");
int i,j,N,G,p[5010],gr[5010];
int D[2][10010];
int maxim;
int main()
{
    f>>N>>G;
    for(i=1;i<=N;i++) f>>gr[i]>>p[i];
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=G;j++)
        {
            if(j<gr[i])
                D[i%2][j]=D[(i-1)%2][j];
            else
                D[i%2][j]=max(D[(i-1)%2][j],D[(i-1)%2][j-gr[i]]+p[i]);
        }
    }
    g<<D[N%2][G];
    f.close();
    g.close();
    return 0;
}
