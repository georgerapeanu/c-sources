#include <bits/stdc++.h>

using namespace std;

int n,m;

vector<pair<int,int> > event[1005];

int type[1005];
int stype[1005];

int main() {
    cin >> n >> m;

    while(m--) {
        int t,l,r;
        cin >> t >> l >> r;
        if(l == r) {
            continue;
        }
        event[l].push_back({t,r - 1});
    }

    int active = 0;

    for(int i = 1; i < n; i++) {
        for(auto it:event[i]) {
            if(it.first == 1) {
                active = max(active,it.second);
            }
        }
        if(active >= i) {
            type[i] = 1;
        }
    }

    for(int i = 1; i < n; i++) {
        stype[i] = type[i] + stype[i - 1];
    }

    for(int i = 1; i < n; i++) {
        for(auto it:event[i]) {
            if(it.first == 0) {
                if(stype[it.second] - stype[i - 1] >= it.second - i + 1) {
                    cout << "NO\n";
                    return 0;
                }
            }
        }
    }

    int lst = 1e9;

    cout << "YES\n" << lst << " ";

    for(int i = 1; i < n; i++) {
        if(type[i] == 1) {
            lst = 1e9;
            cout << lst << " ";
        }
        else {
            lst--;
            cout << lst << " ";
        }
    }


    return 0;
}
