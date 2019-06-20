#include <bits/stdc++.h>

using namespace std;

const int TMAX = 1e5;
const int NMAX = 2000;
const int MMAX = 2000;
const int SIGMA = 30;
const int inf = 1e5;
int t;
int n,m;
string s[NMAX + 5];

void solve() {
    cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] = " " + s[i];
    }

    vector<int> x_max(SIGMA + 5,-inf);
    vector<int> x_min(SIGMA + 5,+inf);
    vector<int> y_max(SIGMA + 5,-inf);
    vector<int> y_min(SIGMA + 5,+inf);

    int ma = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(s[i][j] != '.') {
                int pos = s[i][j] - 'a' + 1;
                ma = max(ma,pos);
                x_max[pos] = max(i,x_max[pos]);
                x_min[pos] = min(i,x_min[pos]);
                y_max[pos] = max(j,y_max[pos]);
                y_min[pos] = min(j,y_min[pos]);
            }
        }
    }

    for(int i = 1; i <= ma; i++) {
        if(x_max[i] != -inf && (x_max[i] != x_min[i]) + (y_max[i] != y_min[i]) > 1) {
            cout << "NO\n";
            return ;
        }
    }

    vector<pair<pair<int,int>,pair<int,int> > > ans;

    int x_free = -1,y_free = -1;

    for(int i = ma; i; i--) {
        if(x_max[i] == -inf) {
            ans.push_back({{x_free,y_free},{x_free,y_free}});
            continue;
        }
        bool ok = true;
        for(int x = x_min[i]; x <= x_max[i]; x++) {
            for(int y = y_min[i]; y <= y_max[i]; y++) {
                ok &= (s[x][y] == 'a' + i - 1 || s[x][y] == '*');
                s[x][y] = '*';
                x_free = x;
                y_free = y;
            }
        }
        if(ok == false) {
            cout << "NO\n";
            return ;
        }
        ans.push_back({{x_min[i],y_min[i]},{x_max[i],y_max[i]}});
    }

    reverse(ans.begin(),ans.end());

    cout << "YES\n";
    cout << ans.size() << "\n";

    for(auto it:ans) {
        cout << it.first.first << " " << it.first.second << " ";
        cout << it.second.first << " " << it.second.second << "\n";
    }
}

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
