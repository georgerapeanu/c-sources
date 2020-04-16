#include <bits/stdc++.h>

using namespace std;

int n,k;
vector<pair<int,int> > vals;

int main() {

    scanf("%d %d",&n,&k);

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        vals.push_back({val,i});
    }

    sort(vals.begin(),vals.end());
    reverse(vals.begin(),vals.end());

    long long ans_a = 0;
    int ans_b = 1;

    vector<int> pos;

    for(int i = 0; i < k; i++) {
        ans_a += vals[i].first;
        pos.push_back(vals[i].second);
    }

    sort(pos.begin(),pos.end());

    for(int i = 1; i < (int)pos.size(); i++) {
        ans_b = 1LL * ans_b * (pos[i] - pos[i - 1]) % 998244353;
    }

    printf("%lld %d\n",ans_a,ans_b);

    return 0;
}
