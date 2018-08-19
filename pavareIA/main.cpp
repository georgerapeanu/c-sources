#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("pavare.in","r");
FILE *g=fopen("pavare.out","w");
int dp[151][20][1<<15];
int N,M,K;
int V[151][151];
bool liber(int conf,int i,int j)
{
    return (((conf>>(j-1))&1)==1&&((conf>>(j-2))&1)==1)&&V[i-1][j]==0&&V[i-1][j-1]==0&&V[i][j]==0&&V[i][j-1]==0;
}
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&K);
    for(int i=1;i<=K;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        V[x][y]=1;
    }
    for(int i=2;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            int st=0;
            for(int k=1;k<=j;k++)if(V[i][k])st|=(1<<(k-1));
            for(int k=j+1;k<=M;k++)if(V[i-1][k])st|=(1<<(k-1));
            for(int conf=st;conf<(1<<M);conf=((conf+1)|st))
            {
                if(j==1)
                {
                    dp[i%2][j][conf]=max(dp[1-i%2][M][conf],dp[1-i%2][M][conf^1]);
                }
                else
                {
                    dp[i%2][j][conf]=max(dp[i%2][j-1][conf],dp[i%2][j-1][conf^(1<<(j-1))]);
                }
                if(j==2&&liber(conf,i,j))
                {
                    dp[i%2][j][conf]=max(dp[i%2][j][conf],dp[1-i%2][M][conf^(3<<(j-2))]+1);
                }
                else if(j>2&&liber(conf,i,j))
                {
                    dp[i%2][j][conf]=max(dp[i%2][j][conf],dp[i%2][j-2][conf^(3<<(j-2))]+1);
                }
            }
        }
    }
    int rez=0;
    for(int conf=0;conf<(1<<M);conf++)rez=max(rez,dp[N%2][M][conf]);
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
