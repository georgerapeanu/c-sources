#include "pswap.h"

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

const int NMAX = 2500;
const int MMAX = 5000;

vector<int> graph[NMAX + 5];

int _n,_m;
int viz[NMAX + 5];
int paired[NMAX + 5];

bool pairup(int nod){
    if(viz[nod]){
        return false;
    }
    viz[nod] = true;

    for(auto it:graph[nod]){
        if(paired[it] == 0){
            paired[nod] = it;
            paired[it] = nod;
            return true;
        }
    }

    for(auto it:graph[nod]){
        if(pairup(paired[it])){
            paired[nod] = it;
            paired[it] = nod;
            return true;
        }
    }
    return false;
}

int cuplaj(){
    int ans = 0;
    bool ok = true;

    while(ok){
        for(int i = 1;i <= _n;i++){
            viz[i] = false;
        }
        ok = false;
        for(int i = 1;i <= _n;i++){
            if(paired[i] == 0 && pairup(i)){
                ans++;
                ok = true;
            }
        }
    }

    return ans;
}

const int BASE = 3001;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 7;
int pw1[MMAX + 5];
int pw2[MMAX + 5];

int add(int a,int b,int mod){
    a += b;
    if(a >= mod){
        a -= mod;
    }
    return a;
}

int scad(int a,int b,int mod){
    a -= b;
    if(a < 0){
        a += mod;
    }
    return a;
}

int mult(int a,int b,int mod){
    return 1LL * a * b % mod;
}

struct hash_t{
    int h1;
    int h2;
    int len;

    hash_t(){
        h1 = 0;
        h2 = 0;
        len = 0;
    }

    hash_t(int val){
        h1 = val;
        h2 = val;
        len = 1;
    }

    hash_t operator + (const hash_t &other)const{
        hash_t ans;
        ans.h1 = add(mult(this->h1,pw1[other.len],MOD1),other.h1,MOD1);
        ans.h2 = add(mult(this->h2,pw2[other.len],MOD2),other.h2,MOD2);
        ans.len = this->len + other.len;
        return ans;
    }

    hash_t ban(int pos,int val){
        hash_t ans;
        ans.h1 = scad(this->h1,mult(pw1[_m - pos],val,MOD1),MOD1);
        ans.h2 = scad(this->h2,mult(pw2[_m - pos],val,MOD2),MOD2);
        ans.len = this->len;
        return ans;
    }

    bool operator == (const hash_t &other)const{
        return this->h1 == other.h1 && this->h2 == other.h2 && this->len == other.len;
    }
};

hash_t hashes[NMAX + 1];
int inv[NMAX + 1][MMAX + 1];
int lcp[NMAX + 1];


int solve(int n, int m, vector<vector<int> > p) {
  
    sort(p.begin(),p.end());

    pw1[0] = 1;
    pw2[0] = 1;

    for(int i = 1;i <= MMAX;i++){
        pw1[i] = 1LL * pw1[i - 1] * BASE % MOD1;
        pw2[i] = 1LL * pw2[i - 1] * BASE % MOD2;
    }

    _n = n;
    _m = m;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            hashes[i] = hashes[i] + hash_t(p[i - 1][j - 1]);
            inv[i][p[i - 1][j - 1]] = j;
        }
    }

    for(int i = 1;i < n;i++){
        while(p[i - 1][lcp[i]] == p[i][lcp[i]]){
            lcp[i]++;
        }
    }

    for(int i = 1;i <= n;i++){
        int len = m;
        for(int j = i + 1;j <= n;j++){
            len = min(len,lcp[j - 1]);
            int fst = len + 1;
            int snd = inv[j][p[i - 1][fst - 1]];
            if(hashes[i].ban(fst,p[i - 1][fst - 1]).ban(snd,p[i - 1][snd - 1]) == 
               hashes[j].ban(fst,p[j - 1][fst - 1]).ban(snd,p[j - 1][snd - 1])){
               graph[i].push_back(j);
               graph[j].push_back(i);
            }
        }
    }

    int tmp = cuplaj();

    return n - tmp;
}
