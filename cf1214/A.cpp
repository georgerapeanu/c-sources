#include <bits/stdc++.h>

using namespace std;

const int LIM = 2e7;

int main() {
    int n,d,e;
    
    cin >> n >> d >> e;
    
    e *= 5;
    
    int ans = n;

    for(int x = 0;x <= n / d && x <= LIM;x++){
        ans = min(ans,((n - x * d) % e));
    }

    for(int x = 0;x <= n / e && x <= LIM;x++){
        ans = min(ans,((n - x * e) % d));
    }

    cout << ans;

    return 0;
}
