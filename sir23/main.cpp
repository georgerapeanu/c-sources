#include <cstdio>
#define MOD 1000000
using namespace std;
FILE *f=fopen("sir23.in","r");
FILE *g=fopen("sir23.out","w");
int N;
int dp[1005][1005];
int S[1005][1005];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=0;i<=N;i++){dp[0][i]=1;S[0][i]=S[0][i-1]+1;}
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            dp[i][j]=dp[i][j-1]+dp[i-1][j-1];
            if(i>1){dp[i][j]=(dp[i][j]+S[i-2][j-1])%MOD;if(dp[i][j]>=MOD)dp[i][j]-=MOD;}
            S[i][j]=S[i][j-1]+dp[i][j];
            if(S[i][j]>=MOD)S[i][j]-=MOD;
        }
    }
    fprintf(g,"%d",dp[N][N]);
    fclose(f);
    fclose(g);
    return 0;
}
