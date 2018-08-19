#include <iostream>
using namespace std;
int dp[1005][1005];
int N,P,K;
int fst[1005];
int fdr[1005];
int main()
{
    cin>>N>>P>>K;
    int dim,val;
    cin>>dim;

    for(int i=1;i<=N;i++)
    {
        dp[i][0]=dp[i-1][0];
        for(int j=1;j<=P;j++)
        {
            dp[i][j]=max(dp[i-1][j],);
        }
    }
    cout<<dp[N][P];
    return 0;
}
