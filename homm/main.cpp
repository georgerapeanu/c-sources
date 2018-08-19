#include <fstream>
using namespace std;
ifstream f("homm.in");
ofstream g("homm.out");
long long H[30][100][100],i,j,N,M,K,stx,sty,fnx,fny,rez,Ma[100][100],p;
int main()
{
    f>>N>>M>>K;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            f>>Ma[i][j];
        }
    }
    f>>stx>>sty>>fnx>>fny;
    H[0][stx][sty]=1;
    for(p=1;p<=K;p++)
        for(i=1;i<=N;i++)
            for(j=1;j<=N;j++)
                if(!Ma[i][j])
                    H[p][i][j]=H[p-1][i-1][j]+H[p-1][i][j+1]+H[p-1][i+1][j]+H[p-1][i][j-1];
    for(i=0;i<=K;i++)
        rez+=H[i][fnx][fny];
    g<<rez;
    return 0;
}
