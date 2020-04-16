#include <bits/stdc++.h>

using namespace std;

int t;
int n,k;
string s;
int dsu[int(2e5 + 5)];
int fr[int(2e5 + 5)]['z' - 'a' + 1];

int fi_root(int nod) {
    if(dsu[nod] == 0) {
        return nod;
    }
    return dsu[nod] = fi_root(dsu[nod]);
}

bool unite(int x,int y) {
    x = fi_root(x);
    y = fi_root(y);

    if(x == y) {
        return false;
    }

    dsu[x] = y;

    for(int i = 0; i <= 'z' - 'a'; i++) {
        fr[y][i] += fr[x][i];
    }

    return  true;
}

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    cin >> t;

    while(t--) {
        cin >> n >> k;
        cin >> s;

        s = " " + s;

        for(int i = 1; i <= n; i++) {
            dsu[i] = 0;
            for(int h = 0; h <= 'z' - 'a'; h++) {
                fr[i][h] = 0;
            }
            fr[i][s[i] - 'a']++;
        }

        for(int i = 1; i <= n; i++) {
            unite(i,n + 1 - i);
            if(i + k <= n) {
                unite(i,i + k);
            }
        }

        int ans = 0;

        for(int i = 1; i <= n; i++) {
            if(dsu[i] == 0) {
                int ma = 0;
                for(int h = 0; h <= 'z' - 'a'; h++) {
                    ans += fr[i][h];
                    ma = max(ma,fr[i][h]);
                }
                ans -= ma;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
