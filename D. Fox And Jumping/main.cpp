#include <iostream>
#include <vector>
using namespace std;
int N;
int dp[(1<<10)];
int L[305];
vector<int> fact[305];
int C[305];
int rez=(1<<29);
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>L[i];
        int l=L[i];
        for(int j=2;1LL*j*j<=l;j++)
        {
            if(l%j==0)
            {
                fact[i].push_back(j);
                while(l%j==0)l/=j;
            }
        }
        if(l!=1)fact[i].push_back(l);
    }
    for(int i=1;i<=N;i++)cin>>C[i];
    for(int i=1;i<=N;i++)
    {
        for(int j=0;j<(1<<fact[i].size());j++)dp[j]=(1<<29);
        dp[(1<<fact[i].size())-1]=C[i];
        for(int j=1;j<=N;j++)
        {
            if(i==j) continue;
            int cod=0;
            for(int k=0;k<fact[i].size();k++)if(L[j]%fact[i][k]==0)cod|=(1<<k);
            for(int k=(1<<fact[i].size())-1;k>=0;k--)
                if(dp[k]!=(1<<29)&&dp[k&cod]>dp[k]+C[j])
                    dp[k&cod]=dp[k]+C[j];
        }
        rez=min(rez,dp[0]);
    }
    cout<<(rez==(1<<29) ? -1:rez);
    return 0;
}
