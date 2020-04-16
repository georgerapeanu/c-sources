#include <bits/stdc++.h>

using namespace std;

string solve(string s) {

    string t = "#";

    for(auto it:s) {
        t += it;
        t += "#";
    }

    s = t;

    vector<int> h(s.size(),0);
    vector<int> pref_pal(s.size() + 2,0);
    vector<int> suff_pal(s.size() + 2,0);

    int bst = 0;

    for(int i = 0; i < (int)s.size(); i++) {
        if(h[bst] + bst > i) {
            h[i] = min(h[2 * bst - i],bst + h[bst] - i);
        }
        while(i - h[i] >= 0 && i + h[i] < (int)s.size() && s[i - h[i]] == s[i + h[i]]) {
            h[i]++;
        }
        if(h[bst] + bst <= h[i] + i) {
            bst = i;
        }
        int lft = i - h[i] + 1;
        int rgt = i + h[i] - 1;
        if(lft + 2 * h[i] - 1 - 1 <= (int)s.size() - 1 - lft) {
            pref_pal[lft] = max(pref_pal[lft],2 * h[i] - 1);
        }
        if((int)s.size() - 1 - rgt <= rgt - 2 * h[i] + 1 + 1) {
            suff_pal[rgt] = max(suff_pal[rgt],2 * h[i] - 1);
        }
    }

    for(int i = 1; i < (int)s.size(); i++) {
        pref_pal[i] = max(pref_pal[i],pref_pal[i - 1] - 2);
    }
    for(int i = (int)s.size() - 2; i >= 0; i--) {
        suff_pal[i] = max(suff_pal[i + 1] - 2,suff_pal[i]);
    }

    int ans = 0;

    int bst_i = 0;
    int bst_mode = 0;

    for(int i = 0; i <= (int)s.size() - 1 - i; i++) {
        if(i + pref_pal[i] - 1 <= (int)s.size() - 1 - i) {
            if(ans < 2 * i + pref_pal[i]) {
                ans = 2 * i + pref_pal[i];
                bst_i = i;
                bst_mode = 0;
            }
        }
        if(i <= (int)s.size() - 1 - i - suff_pal[(int)s.size() - 1 - i] + 1) {
            if(ans < 2 * i + suff_pal[(int)s.size() - 1 - i]) {
                ans = 2 * i + suff_pal[(int)s.size() - 1 - i];
                bst_i = i;
                bst_mode = 1;
            }
        }
        if(ans < 2 * i) {
            ans = 2 * i;
            bst_mode = 2;
        }
        if(s[i] != s[(int)s.size() - 1 - i]) {
            break;
        }
    }


    string pref = "",middle = "";

    for(int j = 0; j < bst_i; j++) {
        pref += s[j];
    }

    if(bst_mode == 0) {
        for(int j = bst_i; j < bst_i + pref_pal[bst_i]; j++) {
            middle += s[j];
        }
    }
    else if(bst_mode == 1) {
        for(int j = (int)s.size() - 1 - bst_i; j > (int)s.size() - 1 - bst_i - suff_pal[(int)s.size() - 1 - bst_i]; j--) {
            middle += s[j];
        }
        reverse(middle.begin(),middle.end());
    }
    string s_ans = pref + middle;
    reverse(pref.begin(),pref.end());
    s_ans = s_ans + pref;

    string r_ans = "";

    for(auto it:s_ans) {
        if(it != '#') {
            r_ans += it;
        }
    }

    return r_ans;
}

int main() {

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    int t;
    cin >> t;

    while(t--) {
        string s;
        cin >> s;
        cout << solve(s) << "\n";
    }

    return 0;
}
