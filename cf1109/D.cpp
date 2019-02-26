#include <cstdio>

using namespace std;

const int NMAX = 1e6;
const int MMAX = 1e6;
const int MOD = (1e9 + 7);

int fact[NMAX + 5];
int ifact[NMAX + 5];

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

int A(int n,int k){
    if(k > n || k < 0){
        return 0;
    }

    return 1LL * fact[n] * ifact[n - k] % MOD;
}

int C(int n,int k){
    if(k > n || k < 0){
        return 0;
    }

    return 1LL * A(n,k) * ifact[k] % MOD;
}

int pr[3 * NMAX + 5];

int add_to_path(int l,int n,int m){

    return 1LL * lgpow(m,n - l - 2) * (1LL * C(n - 2,l) * lgpow(n - 1,n - 2 - l) % MOD)  % MOD;
}

int f(int x,int y){
    if(x - y - 1 < 0){
        return 1;
    }

    return 1LL * y * lgpow(x,x - y - 1) % MOD;
}

int main(){

    fact[0] = 1;

    for(int i = 1;i <= NMAX;i++){
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }

    pr[1] = 1;
    pr[2] = 2;

    for(int i = 3;i <= 3 * NMAX;i++){
        pr[i] = 1LL * i * pr[i - 2] % MOD;
    }

    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);

    for(int i = NMAX - 1;i >= 0;i--){
        ifact[i] = 1LL * (i + 1) * ifact[i + 1] % MOD;
    }

    int n,m,a,b;
    scanf("%d %d %d %d",&n,&m,&a,&b);

    int ans = 0;

    for(int l = 0;l <= n - 2;l++){
        int tmp = A(n - 2,l);
        tmp = 1LL * tmp * C(m - 1,l) % MOD;
        tmp = 1LL * tmp * lgpow(m,n - 1 - l - 1) % MOD;
        tmp = 1LL * tmp * f(n,l + 2) % MOD;
        ans = (ans + tmp) % MOD;
    }

    printf("%d",ans);


    return 0;
}
