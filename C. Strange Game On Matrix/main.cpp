#include <iostream>
using namespace std;
int N,M,K;
int V[105][105];
int dp[105][105];
int S[105][105];
int rez,b,nr;
int main()
{
    cin>>N>>M>>K;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            cin>>V[i][j];
    for(int i=N;i;i--)
        for(int j=1;j<=M;j++)
            S[i][j]=V[i][j]+S[i+1][j];
    for(int j=1;j<=M;j++)
    {
        nr=0;
        for(int i=N;i;i--)
        {
            dp[i][j]=dp[i+1][j];
            if(V[i][j]==1)
            {
                if(dp[i][j]<S[i][j]-S[min(N+1,i+K)][j])
                {
                    nr=S[1][j]-S[i][j];
                    dp[i][j]=S[i][j]-S[min(N+1,i+K)][j];
                }
                else if(dp[i][j]==S[i][j]-S[min(N+1,i+K)][j])
                {
                    nr=min(nr,S[1][j]-S[i][j]);
                }
            }
            else
                dp[i][j]=dp[i+1][j];
        }
        rez+=dp[1][j];
        b+=nr;
    }
    cout<<rez<<" "<<b;
    return 0;
}
