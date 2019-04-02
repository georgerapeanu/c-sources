#include <iostream>

using namespace std;

int main() {
    long long n,x,y;

    cin >> n >> x >> y;

    long long bucks = n / x;

    if(bucks > 0) {
        cout << x - 1;
        return 0;
    }

    long long ans = 0;

    ///a + n - 1 < x;
    if((y - (n - 1) * n / 2) % n == 0) {
        long long a = (y - (n - 1) * n / 2) / n;
        if(!(a < 0 || a + n - 1 >= x)) {
            ans = max(ans,a + n - 1);
        }
    }

    ///a + n - 1 >= x

    for(long long over_x = 0; over_x <= n; over_x++) {
        long long lst = x - (n - over_x);
        if((y - over_x * (over_x - 1) / 2) - (x - 1 + lst) * (n - over_x) / 2 == 0) {
            ans = max(ans,(over_x == n ? n - 1:x - 1));
        }
    }

    cout << ans;


    return 0;
}
