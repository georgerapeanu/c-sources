#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int LGMAX = 17;
const int NMAX = 2e5;

int n;
string t;
int q;
int pref[NMAX + 5];

const int BASE = 37;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

int pw1[NMAX + 5];
int pw2[NMAX + 5];
struct hsh_t{
    int len;
    int h1;
    int h2;

    hsh_t(){
        len = 0;
        h1 = h2 = 0;
    }

    hsh_t(int val){
        h1 = h2 = val;
        len = 1;
    }

    hsh_t operator + (const hsh_t &other)const{
        hsh_t ans;
        ans.len = this->len + other.len;
        ans.h1 = (1LL * this->h1 * pw1[other.len] + other.h1) % MOD1;
        ans.h2 = (1LL * this->h2 * pw2[other.len] + other.h2) % MOD2;
        return ans;
    }

    bool operator == (const hsh_t &other)const{
        return this->len == other.len && this->h1 == other.h1 && this->h2 == other.h2;
    }
};

hsh_t rmq[LGMAX + 1][NMAX + 1][2];

pair<hsh_t,hsh_t> get_rmq_hash(int x,int y){
    hsh_t ans1,ans2;
    for(int h = LGMAX;h >= 0;h--){
        if((y - x + 1) >= (1 << h)){
            ans1 = rmq[h][y][0] + ans1;
            ans2 = rmq[h][y][1] + ans2;
            y -= (1 << h);
        }
    }
    return {ans1,ans2};
}

int main()
{
    pw1[0] = pw2[0] = 1;

    for(int i = 1;i <= NMAX;i++){
        pw1[i] = 1LL * BASE * pw1[i - 1] % MOD1;
        pw2[i] = 1LL * BASE * pw2[i - 1] % MOD2;
    }

    cin >> n;
    cin >> t;
    cin >> q;

    t = " " + t;

    for(int i = 1;i <= n;i++){
        if(t[i] == '0'){
            pref[i] = 1 + pref[i - 1];
            rmq[0][i][0] = hsh_t(i % 2);
            rmq[0][i][1] = hsh_t(1 - (i % 2));
        }
        else{
            pref[i] = pref[i - 1];
            rmq[0][i][0] = hsh_t();
            rmq[0][i][1] = hsh_t();
        }
    }

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= n;i++){
            if(i - (1 << (h - 1)) <= 0){
                rmq[h][i][0] = rmq[h - 1][i][0];
                rmq[h][i][1] = rmq[h - 1][i][1];
            }
            else{
                rmq[h][i][0] = rmq[h - 1][i - (1 << (h - 1))][0] + rmq[h - 1][i][0];
                rmq[h][i][1] = rmq[h - 1][i - (1 << (h - 1))][1] + rmq[h - 1][i][1];
            }
        }
    }

    while(q--){
        int x,y,l;
        cin >> x >> y >> l;

        if(pref[x + l - 1] - pref[x - 1] != pref[y + l - 1] - pref[y - 1]){
            cout << "No\n";
            continue;
        }

        pair<hsh_t,hsh_t> a = get_rmq_hash(x,x + l - 1);
        pair<hsh_t,hsh_t> b = get_rmq_hash(y,y + l - 1);

        if(((x - 1)) % 2 == 1){
            swap(a.first,a.second);
        }

        if(((y - 1)) % 2 == 1){
            swap(b.first,b.second);
        }

        cout << (a.first == b.first ? "Yes\n":"No\n");
    }

    return 0;
}

