#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("tren1.in","r");
FILE *g=fopen("tren1.out","w");
int i,j,N,M,S[50005],dp[4][50005],maxim;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&S[i]);
        S[i]=S[i-1]+S[i];
    }
    fscanf(f,"%d",&M);
    for(i=1;i<=3;i++)
    {
        maxim=dp[i-1][(i-1)*M];
        for(j=i*M;j<=N;j++)
        {
            dp[i][j]=S[j]-S[j-M]+maxim;
            maxim=max(maxim,dp[i-1][j-M+1]);
        }
    }
    maxim=0;
    for(i=3*M;i<=N;i++)
        if(dp[3][i]>maxim)
            maxim=dp[3][i];
    fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
