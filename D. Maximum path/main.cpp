#include <iostream>
using namespace std;
long long dp[4][100005];
long long S[4][100005];
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=3;i++)
        for(int j=1;j<=N;j++)
            cin>>S[i][j];
    for(int j=1;j<=N;j++)
    {
        dp[3][j]=min(dp[3][j-1])
    }
    return 0;
}
