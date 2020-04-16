#include <bits/stdc++.h>

using namespace std;

int dp[32];

int main() {
    int t;
    int d,m;

    cin >> t;

    while(t--) {
        cin >> d >> m;

        int ans = 1;

        for(int i = 0; i <= 30; i++) {
            if((1 << i) > d) {
                break;
            }
            ans = (ans + 1LL * ans * (min(d + 0LL,(1LL << (i + 1)) - 1) - (1 << i) + 1)) % m;
        }
        ans--;
        if(ans < 0)ans += m;
        cout << ans << "\n";
    }
    return 0;
}
