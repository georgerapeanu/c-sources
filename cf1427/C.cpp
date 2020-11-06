#include <bits/stdc++.h>

using namespace std;

int n,r;
vector<pair<int,pair<int,int> > > v;
vector<int> dp;
vector<int> sdp;

int main() {
    scanf("%d %d",&r,&n);

    v.reserve(n + 1);
    dp.reserve(n + 1);
    sdp.reserve(n + 1);

    dp.push_back(0);
    v.push_back({0,{1,1}});


    for(int i = 1;i <= n;i++){
        int t,x,y;
        scanf("%d %d %d",&t,&x,&y);
        v.push_back({t,{x,y}});
        dp.push_back(-1e9);
        sdp.push_back(0);
    }

    for(int i = 1;i <= n;i++){
        for(int j = i - 1;j >= 0;j--){
            if(v[i].first - v[j].first > 2 * r){
                dp[i] = max(dp[i],sdp[j] + 1);
                break;
            }
            else if(abs(v[i].second.first - v[j].second.first) + abs(v[i].second.second - v[j].second.second) + v[j].first <= v[i].first){
                dp[i] = max(dp[i],dp[j] + 1);
            }
        }
        sdp[i] = max(sdp[i - 1],dp[i]);
    }

    printf("%d\n",sdp[n]);

    return 0;
}
