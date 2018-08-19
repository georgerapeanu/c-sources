#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
int dp[1<<20];
int of[155],cost[155];
int N,M;
int rconf;
int nr,val;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>nr;
        of[i]|=(1<<(i-1));
        cost[i]=nr;
    }
    cin>>M;
    for(int i=N+1;i<=N+M;i++)
    {
        cin>>cost[i];
        cin>>nr;
        for(int j=1;j<=nr;j++)
        {
            cin>>val;
            of[i]|=(1<<(val-1));
        }
    }
    cin>>nr;
    for(int i=1;i<=nr;i++)
    {
        cin>>val;
        rconf|=(1<<(val-1));
    }
    memset(dp,1,sizeof(dp));
    dp[0]=0;
    int rez=(1<<30);
    for(int conf=0;conf<(1<<20);conf++)
    {
        for(int i=1;i<=N+M;i++)
        {
            dp[conf|of[i]]=min(dp[conf|of[i]],dp[conf]+cost[i]);
        }
        if((conf&(rconf))==rconf)
            rez=min(rez,dp[conf]);
    }
    cout<<rez;
    return 0;
}
