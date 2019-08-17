#include <bits/stdc++.h>

using namespace std;

int n,m,k;
int h[105];

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.sync_with_stdio(0);
    cout.tie(0);

    int t;
    cin >> t;

    while(t--) {
        cin >> n >> m >> k;

        for(int i = 1; i <= n; i++) {
            cin >> h[i];
        }

        bool ok = true;

        for(int i = 1; i < n; i++) {
            h[i] += m;
            m = 0;
            if(h[i] + k < h[i + 1]) {
                ok = false;
                break;
            }
            else {
                m = h[i] - max(0,(h[i + 1] - k));
            }
        }

        cout << (ok == true ? "YES":"NO") << "\n";
    }
    return 0;
}
