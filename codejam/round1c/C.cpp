#include <bits/stdc++.h>

using namespace std;

int tests;
string s,e;
deque<int> a,b;

deque<int> transform(string s) {
    deque<int> ans;
    int len = 0;
    int last = -1;
    for(auto it:s) {
        if(last != it) {
            if(len > 0) {
                ans.push_back(len);
            }
            len = 0;
            last = it;
        }
        len++;
    }
    if(len > 0) {
        ans.push_back(len);
    }
    return ans;
}

int solve(string s,string e) {
    a = transform(s);
    b = transform(e);
    int bonus = 0;
    int ans = 1e9;
    if(int(a.size() + (a.size() & 1)) < b.size()) {
        return -1;
    } else {
        if(a.size() + (a.size() & 1) >= b.size() && (int(a.size()) - 1) + ((int(a.size()) - 1) % 2) < b.size()){
            bonus = 1;
            a.push_back(1);
        }
        for(int i = max(0,(int)(a.size() - b.size())); i < (int)a.size(); i++) {
            bool ok_suff = true;
            for(int j = i; j < (int)a.size() - 1; j++) {
                if(b[j - i] != a[j]) {
                    ok_suff = false;
                    break;
                }
            }
            if(b[(int)a.size() - 1 - i] == a.back() || (b[(int)a.size() - 1 - i] > a.back() && (i != 0 || ((int)a.size() % 2 == 0)))){
            }else{
                ok_suff = false;
            }
            if(ok_suff) {
                int local_ans = i + (b[(int)a.size() - 1 - i] - a.back());
                for(int j = (int)a.size() - i; j < (int)b.size(); j++) {
                    local_ans += b[j];
                }
                ans = min(ans,local_ans);
            }
        }
        int local_ans = (int)a.size();
        for(auto it:b) {
            local_ans += it;
        }
        ans = min(local_ans,ans);
        return bonus + ans;
    }
}

int main() {

    cin >> tests;

    for(int test = 1; test <= tests; test++) {
        cout << "Case #" << test << ": ";
        cin >> s >> e;
        if(s == e) {
            cout << 0;
        } else if(s == "0") {
            s = "1";
            int ans = (e == "1" ? 0:solve(s,e));
            if(ans == -1) {
                cout << "IMPOSSIBLE";
            } else {
                cout << ans + 1;
            }
        } else if(e == "0") {
            cout << transform(s).size();
        } else {
            int ans = solve(s,e);
            if(ans == -1) {
                cout << "IMPOSSIBLE";
            } else {
                cout << ans;
            }
        }
        cout << "\n";
    }

    return 0;
}
