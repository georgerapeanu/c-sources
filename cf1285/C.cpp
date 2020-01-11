#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a,long long b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

int main() {

    long long x;
    cin >> x;

    long long ans = 1e18;

    for(int i = 1; 1LL * i * i <= x; i++) {
        if(x % i == 0 && gcd(i,x / i) == 1) {
            ans = min(ans,max(1LL * i,x / i));
        }
    }

    cout << x / ans << " " << ans;

    return 0;
}
