#include <cstdio>
#define MOD 666013
using namespace std;
FILE *f=fopen("contrasens.in","r");
FILE *g=fopen("contrasens.out","w");
long long dp[100005][6],rez;
int N,P,i,j;
char ok;
int main()
{
    fscanf(f,"%d %d\n",&N,&P);
    dp[0][1]=dp[0][2]=dp[0][3]=dp[0][4]=1;
    dp[1][1]=dp[1][4]=1;
    for(j=2;j<=3;j++)
    {
        ok=fgetc(f);
        dp[1][j]='1'-ok;
    }
    ok=fgetc(f);
    for(i=2;i<=N;i++)
    {
        dp[i][1]=(dp[i-1][1]+dp[i-1][2]-(i>P ? dp[i-P-1][2]:0))%MOD;
        dp[i][4]=(dp[i-1][4]+dp[i-1][3]-(i>P ? dp[i-P-1][3]:0))%MOD;
        for(j=2;j<=3;j++)
        {
            ok=fgetc(f);
            if(ok=='0')
                dp[i][j]=(dp[i-1][j-1]+dp[i-1][j]+dp[i-1][j+1])%MOD;
        }
        ok=fgetc(f);
    }
    rez=(dp[N][1]+dp[N][2]+dp[N][3]+dp[N][4])%MOD;
    if(rez<0)
        rez=rez%MOD+MOD;
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
