#include <cstdio>
#include <algorithm>
#define LEN 1000
#define BASE 10000
using namespace std;
FILE *f=fopen("petrecere.in","r");
FILE *g=fopen("petrecere.out","w");
int dp[2][LEN];
int N;
void mul(int A[],int nr)
{
    int t=0;
    for(int i=1;i<=A[0]||t;i++)
    {
        A[0]=max(A[0],i);
        A[i]=A[i]*nr+t;
        t=A[i]/BASE;
        A[i]%=BASE;
    }
}
void add(int A[],int B[])
{
    int t=0;
    for(int i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[i]=A[i]+B[i]+t;
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(i,A[0]);
    }
}
int main()
{
    dp[1][0]=dp[1][1]=1;
    dp[0][0]=1;dp[0][1]=2;
    fscanf(f,"%d",&N);
    for(int i=3;i<=N;i++)
    {
        mul(dp[i%2],i-1);
        add(dp[i%2],dp[1-i%2]);
    }
    fprintf(g,"%d",dp[N%2][dp[N%2][0]]);
    for(int i=dp[N%2][0]-1;i;i--)
    {
        int cb=BASE/10;
        while(cb>dp[N%2][i])
        {
            fputc('0',g);
            cb/=10;
        }
        if(dp[N%2][i])
            fprintf(g,"%d",dp[N%2][i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
