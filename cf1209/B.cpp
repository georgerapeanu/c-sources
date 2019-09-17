#include <bits/stdc++.h>

using namespace std;

int n;
string s;
int a[105],b[105];

const int LEN = 240;

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    cin >> n;
    cin >> s;

    for(int i = 1; i<= n; i++) {
        cin >> a[i] >> b[i];
    }

    int ans = 0;

    for(int t = 0; t <= LEN; t++) {
        int cnt = 0;
        for(auto it:s) {
            cnt += (it == '1');
        }
        ans = max(ans,cnt);
        for(int i = 0; i < n; i++) {
            if(t >= b[i + 1] && ((t - b[i + 1]) % a[i + 1] == 0)) {
                s[i] = (1 - (s[i] - '0')) + '0';
            }
        }
    }

    cout << ans;

    return 0;
}
