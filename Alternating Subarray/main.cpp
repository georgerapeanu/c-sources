#include <iostream>
using namespace std;
int dp[100005][2];
int N,V[100005],rez;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        if(V[i]>V[i-1])
        {
            dp[i][0]=dp[i-1][1]+1;
            dp[i][1]=1;
        }
        else if(V[i]<V[i-1])
        {
            dp[i][0]=1;
            dp[i][1]=dp[i-1][0]+1;
        }
        else
            dp[i][0]=dp[i][1]=1;
        if(rez<dp[i][0])
            rez=dp[i][0];
        else if(dp[i][1]>rez)
            rez=dp[i][1];
    }
    cout<<rez;
    return 0;
}
