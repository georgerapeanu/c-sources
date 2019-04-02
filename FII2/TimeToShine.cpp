#include <iostream>

using namespace std;

int n;
int a[int(1e5) + 5];

int main() {

    cin >> n;

    long long ans = 0;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += a[i];
    }

    ans = ans * ans;

    for(int i = 1; i <= n; i++) {
        ans -= 1LL * a[i] * a[i];
    }

    ans /= 2;

    cout << ans;

    return 0;
}
