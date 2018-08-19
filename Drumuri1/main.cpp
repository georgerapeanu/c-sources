#include <cstdio>
#include <queue>
#include <bitset>
#define MOD 31607
using namespace std;
FILE *f=fopen("drumuri1.in","r");
FILE *g=fopen("drumuri1.out","w");
int N,K,L,M,x,y,rez;
int dp[251][251][251];
bool B[251][251];
int main()
{
    fscanf(f,"%d%d%d%d",&N,&M,&K,&L);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d",&x,&y);
        B[x][y]=1;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            for(int k=B[i][j];k<=K;k++)
            {
                dp[i%2][j][k]=(dp[i%2][j-1][k-B[i][j]]+dp[1-(i%2)][j][k-B[i][j]])%MOD;
            }
            if(B[i][j])
                dp[i%2][j][0]=0;
            if(i==1&&j==1)
                dp[1][1][B[1][1]]=1;
            if(i+j-1==L)
                rez=(rez+dp[i%2][j][K])%MOD;
        }
    }
    fprintf(g,"%d",rez);
    return 0;
}
///i+j-1=L=>j=L+1-i
///l-i+1<=N
///l-i<=N-1
///i>=1+l-N
