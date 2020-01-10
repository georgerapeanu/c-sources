#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int NMAX = 1e6;

int n;
vector<int> items[NMAX + 5];
map<int,int> fr;

int lgpow(int base,int exp) {
    int ans = 1;

    while(exp) {
        if(exp & 1) {
            ans = 1LL * ans * base % MOD;
        }
        exp >>= 1;
        base = 1LL * base * base % MOD;
    }

    return ans;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int len;
        scanf("%d",&len);

        while(len--) {
            int x;
            scanf("%d",&x);
            items[i].push_back(x);
            fr[x]++;
        }
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < (int)items[i].size(); j++) {
            int prob = lgpow((1LL * (1LL * n * (int)items[i].size() % MOD) * n) % MOD,MOD - 2);
            prob = 1LL * prob * (fr[items[i][j]]) % MOD;
            ans += prob;
            if(ans >= MOD) {
                ans -= MOD;
            }
        }
    }

    printf("%d\n",ans);

    return 0;
}
