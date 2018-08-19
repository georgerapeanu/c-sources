#include <cstdio>
#include <algorithm>
#define BASE 100000
#define LEN 500
using namespace std;
FILE *f=fopen("expozitie.in","r");
FILE *g=fopen("expozitie.out","w");
int N,K,D;
int dp[2][505][LEN];
void add(int A[],int B[])
{
    int t=0;
    for(int i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[i]=(i<=A[0] ? A[i]:0)+(i<=B[0] ? B[i]:0)+t;
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(i,A[0]);
    }
}
int main()
{
    fscanf(f,"%d%d%d",&N,&D,&K);
    N-=K*D;
    if(N<0)
    {
        fputc('0',g);return 0;
    }
    if(N==0)
    {
        fputc('1',g);return 0;
    }
    dp[0][0][0]=dp[0][0][1]=1;
    for(int i=1;i<=D;i++)
    {
        for(int j=0;j<=N;j++)
        {
            dp[i%2][j][0]=0;
            add(dp[i%2][j],dp[(i-1)%2][j]);
            if(j)
                add(dp[i%2][j],dp[i%2][j-1]);
        }
    }
    fprintf(g,"%d",dp[D%2][N][dp[D%2][N][0]]);
    for(int i=dp[D%2][N][0]-1;i;i--)
    {
        int cb=BASE/10;
        while(dp[D%2][N][i]<cb)
        {
            cb/=10;
            fputc('0',g);
        }
        if(dp[D%2][N][i])
            fprintf(g,"%d",dp[D%2][N][i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
