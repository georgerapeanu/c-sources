#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("sotron.in","r");
FILE *g=fopen("sotron.out","w");
int N,i,j,M[300][300],dp[300][300],rez;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
            fscanf(f,"%d",&M[i][j]);
    }
    for(i=1;i<=N;i++)
    {
        for(j=N;j>=1;j--)
        {
            if(!((i+j)&1))
            {
                dp[i][j]=max(M[i][j],M[i][j]+dp[i-1][j]);
            }
            else
            {
                dp[i][j]=max(M[i][j],M[i][j]+dp[i][j+1]);
            }
        }
    }
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            rez=max(rez,dp[i][j]);
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
