#include <bits/stdc++.h>

using namespace std;

const int NMAX = 4000;
const int MMAX = 4000;

const int BASE = 31;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

struct hash_t{
    int h1,h2;

    hash_t(){
        h1 = h2 = 0;
    }

    hash_t(int h1,int h2){
        this->h1 = h1;
        this->h2 = h2;
    }

    void add(char c){
        int val = c - 'a' + 1;
        h1 = (1LL * h1 * BASE + val) % MOD1;
        h2 = (1LL * h2 * BASE + val) % MOD2;
    }

    hash_t operator * (const hash_t &other)const{
        hash_t ans;
        ans.h1 = 1LL * this->h1 * other.h1 % MOD1;
        ans.h2 = 1LL * this->h2 * other.h2 % MOD2;
        return ans;
    }

    hash_t operator - (const hash_t &other)const{
        hash_t ans;

        ans.h1 = ((this->h1 - other.h1) % MOD1 + MOD1) % MOD1;
        ans.h2 = ((this->h2 - other.h2) % MOD2 + MOD2) % MOD2;

        return ans;
    }


    bool operator == (const hash_t &other)const{
        return this->h1 == other.h1 && this->h2 == other.h2;
    }
};

hash_t pw[NMAX + 5];

int n;
int m;
int _len[MMAX + 5];
hash_t wordhashes[MMAX + 5];
hash_t prefhashes[NMAX + 5];
string s;

const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;

    if(a >= MOD){
        a -= MOD;
    }

    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}


int dp[NMAX + 5];

int main(){

    pw[0] = {1,1};
    for(int i = 1;i <= MMAX;i++){
        pw[i].h1 = 1LL * pw[i - 1].h1 * BASE % MOD1;
        pw[i].h2 = 1LL * pw[i - 1].h2 * BASE % MOD2;
    }

    cin >> n >> m;
    cin >> s;
    s = " " + s;

    prefhashes[0] = hash_t();

    for(int i = 1;i <= n;i++){
        prefhashes[i] = prefhashes[i - 1];
        prefhashes[i].add(s[i]);
    }

    for(int i = 1;i <= m;i++){
        string tmp;
        cin >> tmp;

        _len[i] = tmp.size();
        wordhashes[i] = hash_t();

        for(auto it:tmp){
            wordhashes[i].add(it);
        }
    }

    dp[0] = 1;

    for(int i = 0;i < n;i++){
        for(int j = 1;j <= m;j++){
            int len = _len[j];
            if(i + len <= n){
                if((prefhashes[i + len] - (prefhashes[i] * pw[len])) == wordhashes[j]){
                    dp[i + len] = add(dp[i + len],dp[i]);
                }
            }
        }
    }

    printf("%d\n",dp[n]);

    return 0;
}

