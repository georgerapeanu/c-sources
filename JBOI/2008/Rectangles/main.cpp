#include <iostream>
#include <algorithm>
using namespace std;
int N;
int dp[1005][1005];
int A[1005];
int B[1005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>A[i]>>B[i];
    dp[1][A[1]]=B[1];
    dp[1][B[1]]=A[1];
    for(int i=2;i<=N;i++)
    {
        dp[i][A[i]]=B[i]+max(dp[i-1][A[i-1]]+abs(A[i]-A[i-1]),dp[i-1][B[i-1]]+abs(A[i]-B[i-1]));
        dp[i][B[i]]=A[i]+max(dp[i-1][A[i-1]]+abs(B[i]-A[i-1]),dp[i-1][B[i-1]]+abs(B[i]-B[i-1]));
    }
    cout<<max(dp[N][A[N]],dp[N][B[N]]);
    return 0;
}
