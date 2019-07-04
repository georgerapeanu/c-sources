#include <bits/stdc++.h>

using namespace std;

int main() {
    int test;

    cin >> test;

    while(test--) {
        int n,s,t;

        cin >> n >> s >> t;
        cout << max(n - t + 1,n - s + 1) << "\n";
    }
    return 0;
}
