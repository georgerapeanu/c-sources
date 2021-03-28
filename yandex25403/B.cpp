#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int NMAX = 1e6;

int n;
int v[NMAX + 5];

int dp[NMAX + 5];

int fact[NMAX + 5];
int ifact[NMAX + 5];

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

int lgpow(int b,int e){
    int p = 1;
    
    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }

    return p;
}

int comb(int n,int k){
    if(k < 0 || k > n){
        return 0;
    }
    return mult(fact[n],mult(ifact[n - k],ifact[k]));
}

int main(){

    fact[0] = 1;
    dp[0] = 1;

    for(int i = 1;i <= NMAX;i++){
        fact[i] = mult(fact[i - 1],i);
        dp[i] = mult(dp[i - 1],2 * i - 1);
    }

    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);

    for(int i = NMAX - 1;i >= 0;i--){
        ifact[i] = mult(ifact[i + 1],i + 1);
    }

    scanf("%d",&n);

    int ans = 0;

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);

        if(v[i] == 1){
            ans = add(ans,mult(mult(dp[i - 1],dp[n - i]),comb(n - 1,i - 1)));
        }
    }

    printf("%d\n",ans);

    return 0;
}
