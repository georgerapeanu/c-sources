#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int n;
vector<int> v;

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        e >>= 1;
        b = 1LL * b * b % MOD;
    }

    return p;
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= 2 * n;i++){
        int a;
        scanf("%d",&a);
        v.push_back(a);
    }

    sort(v.begin(),v.end());

    int ans = 0;

    for(int i = 0;i < 2 * n;i++){
        if(i < n){
            v[i] %= MOD;
            ans = (MOD + ans - v[i]) % MOD;
        }
        else{
            v[i] %= MOD;
            ans = (ans + v[i]) % MOD;
        }
    }

    int ifact = 1;

    for(int i = 1;i <= 2 * n;i++){
        if(i <= n){
            ifact = 1LL * ifact * i % MOD;
        }
        else{
            ans = 1LL * ans * i % MOD;
        }
    }

    ifact = lgpow(ifact,MOD - 2);      

    ans = 1LL * ans * ifact % MOD;

    printf("%d\n",ans);

    return 0;
}
