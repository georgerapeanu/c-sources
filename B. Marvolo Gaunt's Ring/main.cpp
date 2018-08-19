#include <iostream>
#include <algorithm>
using namespace std;
long long rez=0;
int V[4],N;
long long A[100005];
long long dp[100005][4];
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=3;i++)cin>>V[i];
    for(int i=1;i<=N;i++)cin>>A[i];
    for(int j=1;j<=3;j++)dp[0][j]=-(1LL<<62);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=3;j++)
        {
            dp[i][j]=-(1LL<<62);
            dp[i][j]=max(dp[i-1][j],dp[i][j-1]+V[j]*A[i]);
        }
    }
    cout<<dp[N][3];
    return 0;
}
