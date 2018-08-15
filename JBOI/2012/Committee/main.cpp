#include <iostream>
using namespace std;
int dp[50005][2];
int N,V[50005];
int rez;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i];
    for(int i=2;i<=N;i++)
    {
        if(V[i]>V[i-1])
        {
            dp[i][1]=dp[i-1][0]+1;
            dp[i][0]=0;
        }
        else
        {
            dp[i][0]=dp[i-1][1]+1;
            dp[i][1]=0;
        }
        if(dp[i][0]>2)rez=max(rez,dp[i][0]-1);
        if(dp[i][1]>2)rez=max(rez,dp[i][1]-1);
    }
    cout<<rez;
    return 0;
}
