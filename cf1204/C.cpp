#include <bits/stdc++.h>

using namespace std;

int n,m;
string s[105];
int v[int(1e6) + 5];
int a[105][105];

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] = " " + s[i];
        for(int j = 1; j <= n; j++) {
            a[i][j] = (s[i][j] == '0' ? 1e5:1);
        }
    }

    cin >> m;

    for(int i = 1; i <= m; i++) {
        cin >> v[i];
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            if(i != k) {
                for(int j = 1; j <= n; j++) {
                    if(k != j && j != i) {
                        a[i][j] = min(a[i][j],a[i][k] + a[k][j]);
                    }
                }
            }
        }
    }

    int lst = 1;
    vector<int> ans;

    ans.push_back(v[1]);

    for(int i = 2; i <= m; i++) {
        if(i != m && i + 1 - lst == a[v[lst]][v[i + 1]]) {
            continue;
        }
        ans.push_back(v[i]);
        lst = i;
    }

    cout << ans.size() << "\n";

    for(auto it:ans) {
        cout << it << " ";
    }


    return 0;
}
