#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int N,K;
int dp[2005][2005];
int maxi[2005];
int s[2005];
int nr[2005];
vector<int> G[2005];
void dfs(int nod,int tata)
{
    dp[nod][0]=1;
    maxi[nod]=nr[nod]=1;
    for(auto it:G[nod]){if(tata!=it){dfs(it,nod);nr[nod]+=nr[it];}}
    for(auto it:G[nod])
        if(tata!=it)
        {
            fill_n(s+1,K+1,1<<30);
            s[0]=dp[nod][0]+dp[it][0];
            for(int j=0;j<=maxi[it]&&j<K+1;j++)
                for(int k=1;k<=maxi[nod]&&k<=K+1-j;k++)
                    s[max(k,j+1)]=min(s[max(k,j+1)],dp[nod][k]+dp[it][j]);
            for(int i=1;i<=K+1;i++)s[i]=min(s[i-1],s[i]);
            memcpy(dp[nod],s,sizeof(s));
            maxi[nod]=max(maxi[nod],maxi[it]+1);
        }
}
int main()
{
    cin>>N>>K;
    for(int i=1;i<N;i++)
    {
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1,0);
    int ans=1<<30;
    for(int i=1;i<=N;i++)
        for(int j=0;j<=K+1;j++)
            ans=min(ans,dp[i][j]+nr[1]-nr[i]);
    cout<<ans;
    return 0;
}
