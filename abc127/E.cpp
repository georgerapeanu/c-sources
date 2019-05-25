#include <cstdio>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 2e5;

int fact[NMAX + 5];
int ifact[NMAX + 5];

int sqr_sum(int x){
    if(x <= 0){
        return 0;
    }

    int a = x;
    int b = x + 1;
    int c = 2 * x + 1;

    if(a % 3 == 0)a /= 3;
    else if(b % 3 == 0)b /= 3;
    else if(c % 3 == 0)c /= 3;
    
    if(a % 2 == 0)a /= 2;
    else if(b % 2 == 0)b /= 2;
    else if(c % 2 == 0)c /= 2;

    return 1LL * (1LL * a * b % MOD) * c % MOD;
}

int num_pairs_with_d(int n,int m,int d){
    ///proof of concept

    int ans = 0;

    if(d - n <= 0){
        ans = (ans + 1LL * (m - 0) * (n + 0 - d)) % MOD;
    }

    if(m >= d){
        ans = (ans + 1LL * (m - d) * (n + d - d)) % MOD;
    }

    int st = max(d - n,1);
    int dr = min(m,d - 1);

    int tmp_norm_sum = (1LL * (dr + st) * (dr - st + 1) / 2) % MOD;
    int tmp_sqr_sum = ((sqr_sum(dr) - sqr_sum(st - 1)) % MOD + MOD) % MOD;

    ans = ((ans + 1LL * (2LL * m * (n - d) % MOD) * (dr - st + 1)) % MOD + MOD) % MOD;
    ans = ((ans + 2LL * tmp_norm_sum * (m - n + d)) % MOD + MOD) % MOD;
    ans = ((ans - 2LL * tmp_sqr_sum) % MOD + MOD) % MOD;
    
    return ans;
}

int comb(int n,int m){
    int ans = 1LL * fact[n] * ifact[m] % MOD;
    ans = 1LL * ans * ifact[n - m] % MOD;
    return ans;
}

int solve(int n,int m,int k,int d){
    int ans = 1;
    ans = 1LL * ans * num_pairs_with_d(n,m,d) % MOD;
    ans = 1LL * ans * comb(n * m - 2,k - 2) % MOD;
    return ans;
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

    int n,m,k;
    int ans = 0;

    scanf("%d %d %d",&n,&m,&k);

    for(int d = 0;d <= n + m;d++){
        ans = (ans + 1LL * d * solve(n,m,k,d)) % MOD;
    }

    printf("%d\n",ans);

    return 0;
}
