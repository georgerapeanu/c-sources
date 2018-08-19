#include <cstring>
#include <cassert>
#include <iostream>
#define MOD 1000000007
using namespace std;
int A[100];
int N;
int T;
int dp[100][205][205];
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>T;
    while(T--)
    {
        for(int i=0;i<100;i++){A[i]=0;for(int j=0;j<205;j++)for(int k=0;k<205;k++)dp[i][j][k]=0;}
        cin>>N;
        for(int i=1;i<=N;i++)cin>>A[i];
        dp[2][A[1]][A[2]]=1;
        for(int i=2;i<99;i++)
        {
            for(int j=0;j<=200;j++)
            {
                for(int k=0;k<=200;k++)
                {
                    if(!dp[i][j][k])continue;
                    for(int l=0;l<=j&&l<=k;l++)
                    {
                        dp[i+1][k-l][A[i+1]+l]+=dp[i][j][k];
                        if(dp[i+1][k-l][A[i+1]+l]>=MOD)dp[i+1][k-l][A[i+1]+l]-=MOD;
                    }
                }
            }
        }
        for(int j=0;j<=99;j++)
            for(int k=0;k<=99;k++)
                if((j||k)&&dp[99][j][k])
                    assert(false);
        cout<<dp[99][0][0]<<"\n";
    }
    return 0;
}
