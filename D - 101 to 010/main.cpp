#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int dp[500005];
vector<int> G[500005];
string s;
int last0=0;
int main()
{
    int N;
    cin>>N>>s;
    s=" "+s;
    for(int i=1;i<=N;i++)
    {
        if(s[i]=='0')
        {
            if(s[i-1]=='1')
            {
                for(int j=i+1;j<=N&&s[j]=='1';j++)
                    G[j].push_back(i-2);
            }
            if(s[i+1]=='1')
            {
                for(int j=i-1;j>0&&s[j]=='1';j--)
                    G[i+1].push_back(j-1);
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        dp[i]=dp[i-1];
        for(auto it:G[i])
            dp[i]=max(dp[i],dp[it]+(i-it-2));
    }
    cout<<dp[N];
    return 0;
}
