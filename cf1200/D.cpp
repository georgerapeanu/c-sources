#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2000;

int n,k;
string s[NMAX + 5];

int up[NMAX + 5];
int lft[NMAX + 5];
int down[NMAX + 5];
int rgt[NMAX + 5];
int cnt[NMAX + 5][NMAX + 5];;

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);
    cin >> n >> k;

    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] = " " + s[i];
        for(int j = 1; j <= n; j++) {
            if(s[i][j] == 'B') {
                down[j] = i;
                rgt[i] = j;
                if(up[j] == 0) {
                    up[j] = i;
                }
                if(lft[i] == 0) {
                    lft[i] = j;
                }
            }
        }
    }

    int base_cnt = 0;
    for(int j = 1; j <= n; j++) {
        if(up[j] == 0) {
            base_cnt++;
        }
        if(lft[j] == 0) {
            base_cnt++;
        }
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        int tmp_cnt = 0;
        for(int j = 1; j <= n; j++) {
            if(up[j] != 0 && down[j] <= i && i - up[j] < k) {
                tmp_cnt++;
            }
            if(j > k && up[j - k] != 0 && down[j - k] <= i && i - up[j - k] < k) {
                tmp_cnt--;
            }
            cnt[i][j] += tmp_cnt;
        }
    }

    for(int i = 1; i <= n; i++) {
        int tmp_cnt = 0;
        for(int j = 1; j <= n; j++) {
            if(lft[j] != 0 && rgt[j] <= i && i - lft[j] < k) {
                tmp_cnt++;
            }
            if(j > k && lft[j - k] != 0 && rgt[j - k] <= i && i - lft[j - k] < k) {
                tmp_cnt--;
            }
            cnt[j][i] += tmp_cnt;
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            ans = max(ans,cnt[i][j]);
        }
    }

    cout << ans + base_cnt;

    return 0;
}
