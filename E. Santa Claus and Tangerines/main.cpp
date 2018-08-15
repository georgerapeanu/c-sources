#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#define LL int
using namespace std;
LL N,K,ma;
LL A[1000005];
int dp[10000005];///cate parti de mandarina de i felii pot obtina care sa aiba cel putin val felii
bool ok(LL val)
{
    LL nr=0;
    for(LL i=1;i<=ma;i++)
    {
        dp[i]=0;
        if(val<=i)
            dp[i]=1;
        if(i%2)
            dp[i]=max(dp[i],dp[i>>1]+dp[(i+1)>>1]);
        else
            dp[i]=max(dp[i],2*dp[i>>1]);
    }
    for(LL i=1;i<=N;i++)
    {
        nr+=dp[A[i]];
        if(nr>=K)
            return 1;
    }
    return 0;
}
int main()
{
    bool notthesamecode=1;
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>K;
    for(LL i=1;i<=N;i++)
        {cin>>A[i];ma=max(ma,A[i]);}
    LL st=0,dr=(1e7+10),mid;
    while(st<dr)
    {
        mid=(st+dr+1)/2;
        if(ok(mid))
            st=mid;
        else
            dr=mid-1;
    }
    if(!st)
        cout<<-1;
    else
        cout<<st;
    return 0;
}
///31 - __builtin_clz(3
