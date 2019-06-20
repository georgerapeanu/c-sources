#include <bits/stdc++.h>

using namespace std;

int t;
string a,b;

vector<pair<char,int> > trans(string a) {
    pair<char,int> tmp = {a[0],0};

    vector<pair<char,int> > v1;

    for(auto it:a) {
        if(it != tmp.first) {
            v1.push_back(tmp);
            tmp.first = it;
            tmp.second = 0;
        }
        tmp.second++;
    }
    v1.push_back(tmp);

    return v1;
}

int main() {

    cin >> t;

    while(t--) {
        cin >> a >> b;
        vector<pair<char,int> > v1,v2;
        v1 = trans(a);
        v2 = trans(b);

        if(v1.size() != v2.size()) {
            cout << "NO\n";
        }
        else {
            bool ok = true;
            for(int i = 0; i < (int)v1.size(); i++) {
                ok &= (v1[i].first == v2[i].first && v1[i].second <= v2[i].second);
            }
            if(ok == false) {
                cout << "NO\n";
            }
            else {
                cout << "YES\n";
            }
        }
    }

    return 0;
}
