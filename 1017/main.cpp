#include <iostream>
using namespace std;
long long dp[505][505];
int N;
int main()
{
    cin>>N;
    dp[0][0]=1;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=i;j++)
        {
            dp[i][j]=dp[i-j][min(j-1,i-j)]+dp[i][j-1];
        }
    }
    cout<<dp[N][N]-1;
    return 0;
}
