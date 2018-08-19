#include <iostream>
#include <algorithm>
using namespace std;
long long dp[100005][2];
int A[100005];
int N;
long long rez;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++) cin>>A[i];
    for(int i=2;i<=N;i++)
    {
        dp[i][0]=max(0LL,dp[i-1][1])+abs(A[i]-A[i-1]);
        dp[i][1]=dp[i-1][0]-abs(A[i]-A[i-1]);
        rez=max(rez,max(dp[i][0],dp[i][1]));
    }
    cout<<rez;
    return 0;
}
