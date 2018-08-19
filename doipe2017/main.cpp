#include <cstdio>
#include <cstring>
#include <iostream>
#define MOD 29997
using namespace std;
FILE *f=fopen("doipe.in","r");
FILE *g=fopen("doipe.out","w");
int dp[2][2005];
int T,N;
char C[2005];
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d\n",&N);
        fgets(C+1,2005,f);
        memset(dp,0,sizeof(dp));
        dp[1][1]=1;
        for(int i=2;i<=N;i++)
        {
            dp[i%2][0]=0;
            if(C[i-1]=='<')
            {
                for(int j=1;j<=i;j++)
                {
                    dp[i%2][j]=dp[1-i%2][j-1]+dp[i%2][j-1];
                    if(dp[i%2][j]>=MOD)dp[i%2][j]-=MOD;
                }
            }
            else
            {
                for(int j=i;j;j--)
                {
                    dp[i%2][j]=dp[1-i%2][j]+dp[i%2][j+1];
                    if(dp[i%2][j]>=MOD)dp[i%2][j]-=MOD;
                }
            }
        }
        int rez=0;
        for(int j=1;j<=N;j++)
        {
            rez+=dp[N%2][j];
            if(rez>=MOD)
                rez-=MOD;
        }
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
