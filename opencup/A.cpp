#include <bits/stdc++.h>

using namespace std;

const int BASE = 1e5;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

int n;
vector<int> v;

map<pair<int,int> ,int> stuff;

void do_hashes(vector<int> &v){
    pair<int,int> hsh = {0,0};
    pair<int,int> pw = {1,1};
    for(int i = 0;i < (int)v.size();i++){
        hsh.first = (1LL * hsh.first * BASE + v[i]) % MOD1;
        hsh.second = (1LL * hsh.second * BASE + v[i]) % MOD2;
        pw.first = 1LL * pw.first * BASE % MOD1;
        pw.second = 1LL * pw.second * BASE % MOD2;
    }   
    for(int i = 0;i < (int)v.size();i++){
        stuff[hsh] = 1;
        hsh.first = (1LL * hsh.first * BASE + v[i]) % MOD1;
        hsh.second = (1LL * hsh.second * BASE + v[i]) % MOD2;
        hsh.first = (MOD1 + ((hsh.first - 1LL * v[i] * pw.first) % MOD1)) % MOD1;
        hsh.second = (MOD2 + ((hsh.second - 1LL * v[i] * pw.second) % MOD2)) % MOD2;
    }

}


int main(){

    while(scanf("%d",&n) == 1){

        stuff.clear();
        v = vector<int>(n,0);
    
        for(int i = 0;i < n;i++){
            scanf("%d",&v[i]);
        }
    
        do_hashes(v);
        reverse(v.begin(),v.end());
        do_hashes(v);

        printf("%d\n",(int)stuff.size());
    }
    return 0;
}
