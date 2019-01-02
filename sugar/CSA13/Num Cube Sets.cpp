#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int MOD1 = 1e9 + 7;
const int MOD2 = 666013;
const int BASE = 3;
const int VMAX = 1e6;
int pw1[VMAX + 5];
int pw2[VMAX + 5];

void init() {
    pw1[0] = 1;
    pw2[0] = 1;
    for(int i = 1; i <= VMAX; i++) {
        pw1[i] = 1LL * pw1[i - 1] * BASE % MOD1;
        pw2[i] = 1LL * pw2[i - 1] * BASE % MOD2;
    }
}

pair<int,int> add_hash(pair<int,int> hsh,pair<int,int> add) {
    int h1,h2;
    h1 = hsh.first;
    h2 = hsh.second;
    h1 = (h1 + 1LL * pw1[add.first] * add.second) % MOD1;
    h1 = (h1 + MOD1) % MOD1;
    h2 = (h2 + 1LL * pw2[add.first] * add.second) % MOD2;
    h2 = (h2 + MOD2) % MOD2;
    return {h1,h2};
}

bool e[VMAX + 5];

pair<int,int> hsh[VMAX + 5];
pair<int,int> op_hsh[VMAX + 5];

int main() {
    init();
    e[0] = e[1] = false;
    for(int i = 2; i <= VMAX; i++) {
        if(!e[i]) {
            for(int j = i; j <= VMAX; j += i) {
                e[j] = true;
                int exp = 0;
                int cj = j;
                while(cj % i == 0) {
                    cj /= i;
                    exp++;
                }
                exp %= 3;
                if(exp == 0);
                else if(exp == 1) {
                    hsh[j] = add_hash(hsh[j], {i,1});
                    op_hsh[j] = add_hash(op_hsh[j], {i,2});
                }
                else if(exp == 2) {
                    hsh[j] = add_hash(hsh[j], {i,2});
                    op_hsh[j] = add_hash(op_hsh[j], {i,1});
                }
            }
        }
    }

    int t;
    cin >> t;
    map<pair<int,int>,int> tmp;
    map<pair<int,int>,int> tmp2;
    while(t--) {
        int n,m;
        cin >> n >> m;
        tmp.clear();
        tmp2.clear();
        long long ans = -1;
        for(int i = 1; i <= n; i++) {
            int val;
            cin >> val;
            tmp[hsh[val]]++;
        }
        for(int i = 1; i <= m; i++) {
            int val;
            cin >> val;
            tmp2[hsh[val]]++;
            int a = tmp[op_hsh[val]];
            int b = tmp2[hsh[val]];
            if(a && b && 1LL * a * a + 1LL * b * b > ans) {
                ans = 1LL * a * a + 1LL * b * b;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}