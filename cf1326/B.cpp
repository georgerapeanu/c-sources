#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    cin >> n;

    int ma = 0;

    for(int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        cout << val + ma << " ";
        ma = max(val + ma,ma);
    }

    return 0;
}
