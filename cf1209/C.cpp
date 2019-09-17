#include <bits/stdc++.h>

using namespace std;

int t;
int n;
string s;

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    cin >> t;

    while(t--) {
        cin >> n;
        cin >> s;

        bool ok = false;

        for(int c = '0'; c <= '9'; c++) {

            int l1 = '0',l2 = c;
            string ans = "";

            for(auto it:s) {
                if(it >= l2) {
                    l2 = it;
                    ans += "2";
                }
                else if(it > c) {
                    ans = "-";
                    break;
                }
                else if(l1 <= it) {
                    l1 = it;
                    ans += "1";
                }
                else {
                    ans = "-";
                    break;
                }
            }

            if(ans[0] != '-') {
                cout << ans << "\n";
                ok = true;
                break;
            }
        }

        if(ok == false)cout << "-\n";

    }

    return 0;
}
