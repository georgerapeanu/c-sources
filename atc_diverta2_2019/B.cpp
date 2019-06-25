#include <bits/stdc++.h>

using namespace std;

int n;
pair<int,int> v[100];

int simulate(int p,int q) {
    int ans = 0;

    for(int i = 1; i <= n; i++) {
        int cost = 1;
        for(int j = 1; j < i; j++) {
            if(v[j].first + p == v[i].first && v[j].second + q == v[i].second) {
                cost = 0;
                break;
            }
        }
        ans += cost;
    }

    return ans;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&v[i].first,&v[i].second);
    }

    sort(v + 1,v + 1 + n);

    int ans = n;

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            ans = min(simulate(v[j].first - v[i].first,v[j].second - v[i].second),ans);
        }
    }

    cout << ans << "\n";

    return 0;
}
