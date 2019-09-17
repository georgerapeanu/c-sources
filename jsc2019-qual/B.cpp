#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int n,k;
int a[2005];

int main() {

    cin >> n >> k;

    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }

    int inner_inv = 0;
    int connected_inv = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            connected_inv += (a[j] > a[i]);
        }
        for(int j = 1;j < i;j++){
            inner_inv += (a[j] > a[i]);
        }
    }

    cout << ((1LL * k * inner_inv % MOD) + ((1LL * connected_inv * ((1LL * (k) * (k - 1) / 2) % MOD)) % MOD)) % MOD << "\n";

    return 0;
}
