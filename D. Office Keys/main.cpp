#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int N,K;
long long A[1005],B[2005],p;
long long dp[1005][2005];
long long solve(int N,int K)
{
    if(!N)return 0;
    if(N==K)return max(solve(N-1,K-1),(long long)(abs(A[N]-B[K])+abs(B[K]-p)));
    return min( max(solve(N-1,K-1),(long long)(abs(A[N]-B[K])+abs(B[K]-p))),solve(N,K-1));
}
int main()
{
    cin>>N>>K>>p;
    for(int i=1;i<=N;i++)cin>>A[i];sort(A+1,A+1+N);
    for(int i=1;i<=K;i++)cin>>B[i];sort(B+1,B+1+K);
    for(int i=1;i<=N;i++)
    {
        for(int j=i;j<=K;j++)
        {
            if(i==j)dp[i][j]=max(dp[i-1][j-1],(long long)(abs(A[i]-B[j])+abs(B[j]-p)));
            else dp[i][j]=min(max(dp[i-1][j-1],(long long)(abs(A[i]-B[j])+abs(B[j]-p))),dp[i][j-1]);
        }
    }
    cout<<dp[N][K];
    return 0;
}
