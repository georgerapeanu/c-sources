#include <bits/stdc++.h>

using namespace std;

int n;
int a[int(1e6) + 5];
pair<int,int> dp[1 << 21];

pair<int,int> join(const pair<int,int> &a,const pair<int,int> &b){
    vector<int> v = {a.first,a.second,b.first,b.second};
    sort(v.begin(),v.end(),[&](int a,int b){return a > b;});
    return {v[0],v[1]};
}

int main() {

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        dp[a[i]] = join(dp[a[i]],{i,0});
    }

    for(int b = 0;b < 21;b++){
        for(int i = 0;i < (1 << 21);i++){
            if(((i >> b) & 1) == 0){
                dp[i] = join(dp[i],dp[i ^ (1 << b)]);
            }
        }
    }

    int ans = 0;

    for(int i = 1;i < dp[0].second;i++){
        int best = 0;
        for(int j = 20;j >= 0;j--){
            if((a[i] >> j) & 1){
                continue;
            }
            if(dp[best ^ (1 << j)].second <= i){
                continue;
            }
            best |= (1 << j);
        }
        ans = max(ans,(best|a[i]));
    }

    printf("%d\n",ans);

    return 0;
}
