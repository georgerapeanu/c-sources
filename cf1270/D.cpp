#include <bits/stdc++.h>

using namespace std;

int n,k;
int a[505];
///pos,val

pair<int,int> ask(set<int> &stuff) {
    cout << "? ";
    for(auto it:stuff) {
        cout << it << " ";
    }
    cout << endl;
    pair<int,int> ans;
    cin >> ans.first >> ans.second;
    return ans;
}

void answer(int k) {
    cout << "! " << k << endl;
    exit(0);
}

int main() {

    cin >> n >> k;

    for(int i = 1; i <= n; i++) {
        a[i] = -1;
    }


    set<int> stuff;

    for(int i = 1; i <= k; i++) {
        stuff.insert(i);
    }

    int lst = k;

    for(int i = 1; i <= n - k + 1; i++) {
        pair<int,int> tmp = ask(stuff);
        a[tmp.first] = tmp.second;
        stuff.erase(tmp.first);
        stuff.insert(++lst);
    }

    stuff.clear();
    set<pair<int,int> > known;
    set<pair<int,int> > unknown;
    for(int i = 1; i <= n; i++) {
        if(a[i] == -1) {
            unknown.insert({i,-1});
            stuff.insert(i);
        }
        else {
            known.insert({i,a[i]});
        }
    }

    stuff.insert(known.begin()->first);
    int ans = known.begin()->second;
    known.erase(known.begin());
    for(int i = 1; i < k; i++) {
        stuff.erase(unknown.begin()->first);
        pair<int,int> tmp = *unknown.begin();
        unknown.erase(tmp);
        pair<int,int> tmp2 = *known.begin();
        stuff.insert(known.begin()->first);
        known.erase(known.begin());
        pair<int,int> res = ask(stuff);
        if(tmp2.second < ans) {
            if(res.second == ans) {
                known.insert({tmp.first,-1e9});
                a[tmp.first] = -1e9;
            }
            else {
                known.insert({tmp.first,1e9});
                a[tmp.first] = 1e9;
            }
        }
        else {
            if(res.second == ans) {
                known.insert({tmp.first,1e9});
                a[tmp.first] = 1e9;
            }
            else {
                known.insert({tmp.first,-1e9});
                a[tmp.first] = -1e9;
            }
        }
        ans = res.second;
    }

    int m = 1;

    for(int i = 1; i <= n; i++) {
        m += (a[i] == -1e9);
    }

    answer(m);

    return 0;
}
