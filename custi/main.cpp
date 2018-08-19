#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("custi.in","r");
FILE *g=fopen("custi.out","w");
int dp[1001][1001];
int frecv[1000001];
int i,j,N,val;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            fscanf(f,"%d",&dp[i][j]);
            if(dp[i][j])
                dp[i][j]=min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]))+1;
            frecv[1]++;
            frecv[dp[i][j]+1]--;
        }
    }
    for(i=1;i<=N;i++)
    {
        val+=frecv[i];
        fprintf(g,"%d\n",val);
    }
    fclose(f);
    fclose(g);
    return 0;
}
