#include <cstdio>
#include <algorithm>
using namespace std;
int dp[2][10005];
int A[10005];
int N;
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&A[i]);
    }
    for(int i=0;i<=A[1];i++)
        dp[1][i]=i+1;
    int l=0;
    for(int i=2;i<=N;i++)
    {
        for(int j=0;j<=A[i];j++)
        {
            int antx=min(j,j-A[i]+A[i-1]);
            if(antx>=0)
            {
                dp[l][j]=dp[l][j-1]+dp[1-l][antx];
                if(dp[l][j]>=123456789)
                    dp[l][j]-=123456789;
            }
            else if(j)
            {
                dp[l][j]=dp[l][j-1];
            }
            else
            {
                dp[l][j]=0;
            }
        }
        l^=1;
    }
    printf("%d",dp[N%2][A[N]]);
    return 0;
}
