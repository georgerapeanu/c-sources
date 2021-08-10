#include <bits/stdc++.h>

using namespace std;

int t;
int n;

const int NMAX = 1e6;
int dp[NMAX + 5];
int dp_real[NMAX + 5];

int main(){

    dp[1] = 1;

    for(int i = 1;i <= NMAX;i++){
        for(int j = 2 * i;j <= NMAX;j += i){
            dp[j] = max(dp[j],dp[i]);
            dp[j + 1] = max(dp[j + 1],dp[i] + 1);
        }
    }

    for(int i = 3;i <= NMAX;i++){
        for(int j = i;j <= NMAX;j += i){
            dp_real[j] = max(dp_real[j],dp[j / i]);
        }
    }


    cin >> t;

    for(int test = 1;test <= t;test++){
        cout << "Case #" << test << ": ";

        cin >> n;

        cout << dp_real[n];
        cout << "\n";
    }

    return 0;
}
