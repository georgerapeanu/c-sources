#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int n,k;
long long sum[NMAX + 5];

int main() {

    cin >> n >> k;

    for(int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum[i] = sum[i - 1] + a;
    }

    long long ans = 1LL * k * sum[n];
    sort(sum + 1,sum + n);
    for(int i = 1; i < k; i++) {
        ans -= sum[i];
    }

    cout << ans << "\n";

    return 0;
}
