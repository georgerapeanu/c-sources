#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;

int n,k,l;
string s;
int a[NMAX + 5];
int b[NMAX + 5];
long long dp[NMAX + 5];
int aux[NMAX + 5];

void check(int a[],int k) {
    deque<int> dq = {0};
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        aux[i] = aux[i - 1];

        while(!dq.empty() && dq.front() < i - l) {
            dq.pop_front();
        }

        if(i >= l && dp[i] < dp[dq.front()] + a[i] - a[dq.front()] - k) {
            dp[i] = dp[dq.front()] + a[i] - a[dq.front()] - k;
            aux[i] = 1 + aux[dq.front()];
        }

        while(!dq.empty() && dp[dq.back()] - a[dq.back()] < dp[i] - a[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
}

int main() {

    cin >> n >> k >> l;
    cin >> s;

    s = " " + s;

    for(int i = 1; i <= n; i++) {
        a[i] = ('a' <= s[i] && s[i] <= 'z');
        b[i] = ('A' <= s[i] && s[i] <= 'Z');

        a[i] += a[i - 1];
        b[i] += b[i - 1];
    }

    int l,r;
    long long ans = n;
    l = -1,r = n + 5;

    while(r - l > 1) {
        int m = (l + r) / 2;
        check(a,m);
        if(aux[n] <= k) {
            r = m;
        }
        else {
            l = m;
        }
    }

    check(a,r);
    ans = min(ans,a[n] - (dp[n] + 1LL * k * r));
    l = -1,r = n + 5;

    while(r - l > 1) {
        int m = (l + r) / 2;
        check(b,m);
        if(aux[n] <= k) {
            r = m;
        }
        else {
            l = m;
        }
    }

    check(b,r);
    ans = min(ans,b[n] - (dp[n] + 1LL * k * r));

    printf("%lld\n",ans);

    return 0;
}
