#include <iostream>

using namespace std;

const int VMAX = 1e6;
const int NMAX = 1e5;

int n;
int dp[VMAX + 5];

int main() {

    for(int i = 1; i <= VMAX; i++) {
        dp[i] = (1 << 28) - 1;
    }

    cin >> n;

    for(int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        dp[val] = val;
    }

    for(int i = VMAX; i; i--) {
        for(int b = 28; b >= 0; b--) {
            if(((i >> b) & 1) == 0 && (i ^ (1 << b)) <= VMAX) {
                dp[i] &= dp[i ^ (1 << b)];
            }
        }
    }

    int ans = 0;

    for(int i = 0; i <= VMAX; i++) {
        ans += (dp[i] == i);
    }

    cout << ans;

    return 0;
}