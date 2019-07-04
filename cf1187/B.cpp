#include <bits/stdc++.h>

using namespace std;

int n;
string s;
string t;
int m;
vector<int> pos[300];
vector<int> fr(300,0);

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    cin >> n;
    cin >> s;

    for(int i = 'a'; i <= 'z'; i++) {
        pos[i].push_back(0);
    }

    for(int i = 0; i < (int)s.size(); i++) {
        pos[s[i]].push_back(i + 1);
    }

    cin >> m;

    while(m--) {
        int ans = 0;

        cin >> t;

        for(auto it:t) {
            fr[it] = 0;
        }

        for(auto it:t) {
            fr[it]++;
        }

        for(auto it:t) {
            ans = max(ans,pos[it][fr[it]]);
        }

        cout << ans << "\n";
    }



    return 0;
}
