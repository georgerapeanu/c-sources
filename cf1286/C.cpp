#include <bits/stdc++.h>

using namespace std;

vector<string> ask(int l,int r) {
    cout << "? " << l << " " << r << endl;
    vector<string> ans;

    string s;

    for(int i = l; i <= r; i++) {
        for(int j = i; j <= r; j++) {
            cin >> s;
            sort(s.begin(),s.end());
            ans.push_back(s);
        }
    }

    sort(ans.begin(),ans.end(),[&](const string &a,const string &b) {
        if(a.size() != b.size())return a.size() < b.size();
        return a < b;
    });

    return ans;
}

void answer(const string &s) {
    cout << "! " << s << endl;
    exit(0);
}

int n;

pair<int,int> stuff[105];

vector<string> cat[105];

int main() {

    cin >> n;

    string ans(n,'0');

    vector<string> tmp,tmp2;

    if(n == 1) {
        tmp = ask(1,n);
        answer(tmp[0]);
        return 0;
    }
    if(n == 2) {
        tmp = ask(1,n);
        tmp2 = ask(1,n - 1);
        if(tmp[2][0] == tmp2[0][0]) {
            answer(tmp[2]);
        }
        else {
            answer(string(1,tmp[2][1]) + string(1,tmp[2][0]));
        }
        return 0;
    }

    ///get first half


    tmp = ask(1,(n + 1) / 2);
    tmp2 = ask(2,(n + 1) / 2);

    map<string,int> fr;

    for(auto it:tmp) {
        fr[it]++;
    }
    for(auto it:tmp2) {
        fr[it]--;
    }

    tmp.clear();

    for(auto it:fr) {
        if(it.second > 0) {
            tmp.push_back(it.first);
        }
    }

    sort(tmp.begin(),tmp.end(),[&](const string &a,const string &b) {
        if(a.size() != b.size())return a.size() < b.size();
        return a < b;
    });

    for(int i = 0; i < (int)tmp.size(); i++) {
        if(i == 0) {
            ans[i] = tmp[0][0];
        }
        else {
            for(int j = 0; j < (int)tmp[i].size(); j++) {
                if(j == (int)tmp[i].size() - 1 || tmp[i][j] != tmp[i - 1][j]) {
                    ans[i] = tmp[i][j];
                    break;
                }
            }
        }
    }

    ///get candidate pairs

    tmp = ask(1,n);

    for(auto it:tmp) {
        cat[it.size()].push_back(it);
    }

    for(int i = 2; i <= (n + 1) / 2; i++) {
        vector<int> fr(30,0);
        for(int j = 0; j < i - 2; j++) {
            fr[ans[j] - 'a'] -= (j + 1);
            fr[ans[n - 1 - j] - 'a'] -= (j + 1);
        }
        for(auto it:cat[i]) {
            for(auto it2:it) {
                fr[it2 - 'a']++;
            }
        }

        vector<char> candidates;

        for(int j = 0; j < 30; j++) {
            if(fr[j] % i == (i - 1)) {
                candidates.push_back('a' + j);
            }
        }

        if(candidates.empty()) {
            ans[n - 1 - (i - 2)] = ans[i - 2];
        }
        else {
            ans[n - 1 - (i - 2)] = candidates[0] ^ candidates[1] ^ ans[i - 2];
        }
    }

    vector<int> fr2(30,0);
    for(auto it:ans) {
        if(it != '0') {
            fr2[it - 'a']--;
        }
    }

    for(auto it:cat[n][0]) {
        fr2[it - 'a']++;
    }

    for(auto &it:ans) {
        if(it == '0') {
            for(int i = 0; i < 30; i++) {
                if(fr2[i] > 0) {
                    fr2[i]--;
                    it = i + 'a';
                }
            }
        }
    }

    answer(ans);

    return 0;
}
