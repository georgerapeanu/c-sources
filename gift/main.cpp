#include <cstdio>
#define MOD 1000000007
using namespace std;
int dp[2000005];
int N,K;
void fix(int &val)
{
    if(val>=MOD)val-=MOD;
    if(val<0)val+=MOD;
}
int main()
{
    scanf("%d%d",&N,&K);
    dp[0]=1;
    for(int i=1;i<=N;i++)
    {
        dp[i]=dp[i-1];
        fix(dp[i]-=(i-K-1>=0 ? dp[i-K-1]:0));
        fix(dp[i]+=dp[i-1]);
    }
    fix(dp[N]-=dp[N-1]);
    printf("%d",dp[N]);
    return 0;
}
