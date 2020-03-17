#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;
int lg2[NMAX + 5];
int dp[NMAX + 5];

int main() {

    lg2[0] = 0;

    for(int i = 1; i <= NMAX; i++) {
        lg2[i] = 1 + lg2[i / 2];
        dp[i] = dp[i / 2] + lg2[i / 2] + 1;
    }

    cout << dp[NMAX];

    return 0;
}
