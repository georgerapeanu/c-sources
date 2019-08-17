#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int LMAX = 1e6;

int n;
string s[NMAX + 5];

const int BASE = 257;
const int MOD1 = 1e9 + 7;
const int MOD2 = 666013;

int pw1[LMAX + 5];
int pw2[LMAX + 5];

struct hsh_t {
    int h1,h2;
    int len;

    hsh_t() {
        h1 = h2 = len = 0;
    }

    void add_front(char c) {
        h1 = (h1 + 1LL * pw1[len] * c) % MOD1;
        h2 = (h2 + 1LL * pw2[len] * c) % MOD2;
        len++;
    }

    void add_back(char c) {
        h1 = (1LL * h1 * BASE + c) % MOD1;
        h2 = (1LL * h2 * BASE + c) % MOD2;
        len++;
    }

    bool operator == (const hsh_t &other)const {
        return h1 == other.h1 && h2 == other.h2;
    }
};

int main() {

    pw1[0] = pw2[0] = 1;

    for(int i = 1; i <= LMAX; i++) {
        pw1[i] = 1LL * pw1[i - 1] * BASE % MOD1;
        pw2[i] = 1LL * pw2[i - 1] * BASE % MOD2;
    }

    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cout.tie(0);

    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    string ans = s[1];

    for(int i = 2; i <= n; i++) {
        int lst_pref = 0;

        int l = (int)ans.size() - 1;
        int r = 0;
        hsh_t fst,snd;
        while(l >= 0 && r < (int)s[i].size()) {
            fst.add_front(ans[l]);
            snd.add_back(s[i][r]);
            if(fst == snd) {
                lst_pref = r + 1;
            }
            l--;
            r++;
        }

        ans += s[i].substr(lst_pref);
    }

    cout << ans;

    return 0;
}
