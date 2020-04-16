#include <bits/stdc++.h>

using namespace std;

int main() {

    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        if(n == 1) {
            cout << -1;
        }
        else if(n % 3 != 1) {
            for(int i = 1; i < n; i++) {
                cout << 2;
            }
            cout << 3;
        }
        else {
            for(int i = 1; i < n - 1; i++) {
                cout << 2;
            }
            cout << 33;
        }
        cout << "\n";
    }

    return 0;
}
