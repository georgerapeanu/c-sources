#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 2e5;

int fact[NMAX + 5];
int ifact[NMAX + 5];

int n,k;

int comb(int n,int k){
    return (1LL * (1LL * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD);
}

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }

    return p;
}

int main(){

    fact[0] = 1;

    for(int i = 1;i <= NMAX;i++){
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }

    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);

    for(int i = NMAX - 1;i >= 0;i--){
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }

    cin >> n >> k;

    k = min(k,n - 1);

    int ans = 0;

    for(int a = 0;a <= k;a++){
        ans = (ans + 1LL * comb(n,a) * comb(n - 1,n - a - 1)) % MOD;
    }

    cout << ans;

    return 0;
}
