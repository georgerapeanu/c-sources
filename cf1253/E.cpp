#include <bits/stdc++.h>

using namespace std;

const int XMAX = 1e5;
const int NMAX = 80;
const int inf = 1e7;

int n,m;
int dp[XMAX + 5];
vector<pair<int,int> > v[XMAX + 5];

int aib[XMAX + 5];

void update(int pos,int val) {
    pos++;
    for(; pos; pos -= (-pos) & pos) {
        aib[pos] = min(aib[pos],val);
    }
}

int query(int pos) {
    pos++;
    int ans = inf;
    for(; pos <= m; pos += (-pos) & pos) {
        ans = min(ans,aib[pos]);
    }
    return ans;
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        aib[i] = inf;
    }

    for(int i = 1; i <= n; i++) {
        int x,s;
        scanf("%d %d",&x,&s);
        for(int j = 0; j <= m && (x - j > 0 || x + j <= m); j++) {
            v[min(x + j,m)].push_back({max(0,x - j - 1),max(0,j - s)});
        }
    }

    dp[0] = 0;
    update(0,0);

    for(int i = 1; i <= m; i++) {
        dp[i] = inf;
        for(auto it:v[i]) {
            dp[i] = min(dp[i],query(it.first) + it.second);
        }
        update(i,dp[i]);
    }

    printf("%d\n",dp[m]);

    return 0;
}
