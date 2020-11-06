#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
int pw10[100005];

string n;
int suff[100005];
int pref[100005];
int ppref[100005];
int ans = 0;

int main() {

    cin >> n;

    pw10[0] = 1;

    for(int i = 1;i < (int)n.size();i++){
        pw10[i] = 10LL * pw10[i - 1] % MOD;
    }

    for(int i = 0;i < (int)n.size();i++){
        pref[i] = ((i > 0 ? pref[i - 1] * 10LL:0) + n[i] - '0') % MOD;
    }

    for(int i = (int)n.size() - 1;i >= 0;i--){
        suff[i] = (1LL * (n[i] - '0') * pw10[(int)n.size() - 1 - i] + (i < (int)n.size() - 1 ? suff[i + 1]:0)) % MOD;
    }

    for(int i = 0;i < (int)n.size();i++){
        ppref[i] = ((i > 0 ? ppref[i - 1]:0) + pref[i]) % MOD;
    }

    for(int j = 0;j < (int)n.size();j++){
        ans = (ans + 1LL * suff[j + 1] * (j + 1) + 1LL * pw10[(int)n.size() - 1 - j] * ppref[j - 1]) % MOD;
    }

    printf("%d\n",ans);

    return 0;
}
