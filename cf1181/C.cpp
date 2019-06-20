#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;

int n,m;
string s[NMAX + 5];
int h[NMAX + 5][NMAX + 5];
int st[NMAX + 5][NMAX + 5];
int len[NMAX + 5];

int main() {

    cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] = " " + s[i];
        for(int j = 1; j <= m; j++) {
            h[i][j] = 1 + (i != 1 && s[i][j] == s[i - 1][j]) * h[i - 1][j];
        }
    }

    long long ans = 0;

    for(int j = 1; j <= m; j++) {
        for(int i = 1; i <= n; i++) {
            while(len[i] > 0 && (s[i][j] != s[i][j - 1] || h[i][st[i][len[i]]] >= h[i][j])) {
                len[i]--;
            }
            st[i][++len[i]] = j;
            if(s[i][j] != s[i][j - 1]) {
                st[i][0] = j - 1;
            }
        }
        for(int i = 1; i <= n; i++) {
            if(i == n || s[i][j] != s[i + 1][j]) {
                int pr = i - h[i][j];
                int ne = i + h[i][j];

                if(pr < 1 || ne > n) {
                    continue;
                }

                int l,r;

                int lft = st[i][len[i] - 1];

                l = 0,r = len[pr] + 1;

                while(r - l > 1) {
                    int mid = (l + r) / 2;
                    if(h[pr][st[pr][mid]] < h[i][j]) {
                        l = mid;
                    }
                    else {
                        r = mid;
                    }
                }

                lft = max(lft,st[pr][l]);

                l = 0,r = len[ne] + 1;

                while(r - l > 1) {
                    int mid = (l + r) / 2;
                    if(h[ne][st[ne][mid]] < h[i][j]) {
                        l = mid;
                    }
                    else {
                        r = mid;
                    }
                }

                lft = max(lft,st[ne][l]);

                ans += j - lft;
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
