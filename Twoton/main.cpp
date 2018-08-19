#include <iostream>
#include <cstdio>
using namespace std;
int N;
int A[100005];
int dp[1000005];
int main()
{
    freopen("twoton.in","r",stdin);
    freopen("twoton.out","w",stdout);
    cin>>N;
    for(int i=1;i<=N;i++)cin>>A[i];
    dp[N]=1;
    for(int i=N-1;i;i--)
    {
        if(A[i]>A[i+1])dp[i]=(1+2*dp[i+1])%19997;
        else           dp[i]=(1+dp[i+1])%19997;
        A[i]=min(A[i],A[i+1]);
    }
    cout<<dp[1];
    return 0;
}
