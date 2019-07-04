#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int MOD = 1e9 + 7;

int n;
int l[NMAX + 5];
int r[NMAX + 5];
double suff_sum[NMAX + 5];

int lgpow(int b,int e) {
    int p = 1;
    while(e) {
        if(e & 1) {
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b %MOD;
        e >>= 1;
    }
    return p;
}

double p_same(int x,int y) {
    double ans = 1;

    int ll = 0,rr = 1e9 + 1;

    for(int i = x; i <= y; i++) {
        ll = max(ll,l[i]);
        rr = min(rr,r[i]);
        ans /= (r[i] - l[i] + 1);
    }

    ans *= max(0,rr - ll + 1);

    return ans;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&l[i]);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d",&r[i]);
    }

    double ans = 1;

    for(int i = 1; i < n; i++) {
        double p = 1 - p_same(i,i + 1);
        ans = ans + 3 * p;
    }

    for(int i = n - 1; i; i--) {
        suff_sum[i] = suff_sum[i + 1] + p_same(i,i + 1);
    }

    for(int i = 1; i < n - 1; i++) {
        ///j = i + 1

        ans += 2 * (1 - p_same(i,i + 1) - p_same(i + 1,i + 2) + p_same(i,i + 2));

        ///j > i + 1
        if(i + 2 < n) {
            ans += 2 * (p_same(i,i + 1) - 1) * (suff_sum[i + 2] - (n - i - 2));
        }
    }

    printf("%.6f\n",ans);

    return 0;
}
