#include <cstdio>
#define MOD 4001
using namespace std;
FILE *f=fopen("div.in","r");
FILE *g=fopen("div.out","w");
int N,K,i,j,l;
short cf[11];
int dp[1005][3];
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&cf[i]);
        dp[1][cf[i]%3]=1;
    }
    for(i=2;i<=K;i++)
    {
        for(j=0;j<=2;j++)
        {
            for(l=1;l<=N;l++)
            {
                dp[i][j]+=dp[i-1][(j-(cf[l]%3)+3)%3];
                dp[i][j]%=MOD;
            }
        }
    }
    fprintf(g,"%d",dp[K][0]);
    fclose(f);
    fclose(g);
    return 0;
}
