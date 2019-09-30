#include <bits/stdc++.h>

using namespace std;

int t;
int a,b;

int main() {

    string s;

    cin >> t;

    while(t--) {
        cin >> a >> b;
        cin >> s;
        int len = 0;
        int cnt = 0;
        for(auto it:s) {
            if(it == '.') {
                len++;
            }
            else {
                len %= (a + b);
                if(len >= a) {
                    cnt++;
                }
                else if(len >= b) {
                    cnt--;
                }
                len = 0;
            }
        }
        cout << (cnt > 0 ? "YES":"NO") << "\n";
    }

    return 0;
}
