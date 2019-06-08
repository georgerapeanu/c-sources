#include <bits/stdc++.h>

using namespace std;

int t;
long long n,k;

int main() {

    cin >> t;
    while(t--) {
        cin >> n >> k;
        long long ans = 0;
        while(n > 1) {
            if(n % k == 0) {
                ans++;
                n /= k;
            }
            else {
                ans += n % k;
                n -= n % k;
            }
        }
        ans += (n > 0);
        cout << ans << "\n";
    }
    return 0;
}
