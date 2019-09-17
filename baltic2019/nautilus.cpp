#pragma GCC optimize("Ofast")
#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;

bitset<505> dp[2][505];
bitset<505> base[505];

int r,c,m;
string s;

int main() {

    cin >> r >> c >> m;

    for(int i = 1; i <= r; i++) {
        cin >> s;
        s = " " + s;
        for(int j = 1; j <= c; j++) {
            base[i][j] = (s[j] == '.');
        }
        dp[0][i] = base[i];
    }

    cin >> s;
    s = " " + s;

    for(int l = 1,k = 1; k <= m; l ^= 1,k++) {
        for(int i = 1; i <= r; i++) {
            dp[l][i].reset();
            if(s[k] == 'N' || s[k] == '?') {
                dp[l][i] |= dp[l ^ 1][i + 1];
            }
            if(s[k] == 'S' || s[k] == '?') {
                dp[l][i] |= dp[l ^ 1][i - 1];
            }
            if(s[k] == 'E' || s[k] == '?') {
                dp[l][i] |= (dp[l ^ 1][i] << 1);
            }
            if(s[k] == 'W' || s[k] == '?') {
                dp[l][i] |= (dp[l ^ 1][i] >> 1);
            }
            dp[l][i] &= base[i];
        }
    }

    int ans = 0;

    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            ans += (dp[m & 1][i][j]);
        }
    }

    cout << ans << "\n";

    return 0;
}
