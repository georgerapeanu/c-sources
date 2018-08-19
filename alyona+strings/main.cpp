#include <iostream>
#include <algorithm>
using namespace std;
int dp[11][1001][1001],K,N,M,i,j,k;
char S[1001],T[1001];
int main()
{
    cin>>N>>M>>K;
    cin.getline(S,1001);
    cin.getline(S+1,1001);
    cin.getline(T+1,1001);
    for(i=1;i<=K;i++)
    {
        for(j=N;j>0;j--)
        {
            for(k=M;k>0;k--)
            {
                if(S[j]==T[k])
                {
                    if(S[j+1]==T[k+1]&&j!=N&&k!=M)
                    {
                        dp[i][j][k]=dp[i][j+1][k+1]+1;
                    }
                    else
                    {
                        dp[i][j][k]=max(max(dp[i-1][j+1][k],dp[i-1][j][k+1])+1,max(dp[i][j+1][k],dp[i][j][k+1]));
                    }
                }
                else
                {
                    dp[i][j][k]=max(dp[i][j][k+1],dp[i][j+1][k]);
                }
            }
        }
    }
    cout<<dp[K][1][1];
    return 0;
}
