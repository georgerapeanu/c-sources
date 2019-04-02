#include <iostream>

using namespace std;

const int NMAX = 1e5;
const int SIGMA = 10;

int dp[NMAX + 5][2];

int best[SIGMA + 5][2];

int n;
int a[NMAX + 5];
int b[NMAX + 5];

int main() {

    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int j = 1; j <= n; j++) {
        cin >> b[j];
    }

    for(int i = n; i > 0; i--) {
        int tmp = a[i];

        while(tmp) {
            dp[i][0] = max(dp[i][0],1 + best[tmp % 10][1]);
            tmp /= 10;
        }

        tmp = b[i];

        while(tmp) {
            dp[i][1] = max(dp[i][1],1 + best[tmp % 10][0]);
            tmp /= 10;
        }

        tmp = a[i];

        while(tmp) {
            best[tmp % 10][0] = max(best[tmp % 10][0],dp[i][0]);
            tmp /= 10;
        }

        tmp = b[i];

        while(tmp) {
            best[tmp % 10][1] = max(best[tmp % 10][1],dp[i][1]);
            tmp /= 10;
        }
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        ans = max(ans,dp[i][0]);
    }

    cout << ans;

    return 0;
}
