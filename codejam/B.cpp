#include <bits/stdc++.h>

using namespace std;

int t;
string s;

int main() {

    cin >> t;

    for(int x = 1; x <= t; x++) {
        cin >> s;

        string ans;

        int h = 0;

        for(auto it:s) {
            while(h < it - '0') {
                ans += '(';
                h++;
            }
            while(h > it - '0') {
                ans += ')';
                h--;
            }
            ans += it;
        }
        while(h > 0) {
            ans += ')';
            h--;
        }
        cout << "Case #" << x << ": " + ans << "\n";
    }

    return 0;
}
