#include <iostream>
#include <cstdio>
#define MOD 64997
using namespace std;
int N,K;
int D[2][2801];
int main()
{
    freopen("robot1.in","r",stdin);
    freopen("robot1.out","w",stdout);
    cin>>N>>K;
    D[1][K]=1;
    int rez=0;
    for(int i=1;i<N;i++)
    {
        for(int j=1;j<=i;j++) D[i%2][j]=0;
        for(int j=i+1;j<=N;j++)
        {
            D[i%2][j]=(D[1-i%2][j]*(j!=N)+(i!=j-1)*D[i%2][j-1])%MOD;
            if(i==1&&j==K) D[i%2][j]=(1+D[i%2][j])%MOD;
        }
        rez=(rez+D[i%2][N])%MOD;;
    }
    cout<<rez;
    return 0;
}
