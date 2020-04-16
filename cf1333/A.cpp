#include <bits/stdc++.h>

using namespace std;

int main() {

    int t;

    cin >> t;

    while(t--) {
        int n,m;
        cin >> n >> m;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if((n * m) % 2 == 0 && ((i ^ j) & 1) == 1 && i == n && j >= m - 1) {
                    cout << 'B';
                }
                else {
                    cout << (((i ^ j) & 1) ? 'W':'B');
                }
            }
            cout << "\n";
        }
    }

    return 0;
}
