#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100;
const int MOD = 1e9 + 7;
const int VMAX = 2e5;

int n;
int fr[NMAX + 5];
int to[NMAX + 5];
int dp[NMAX + 5][NMAX + 5];

int fact[VMAX + 5];
int ifact[VMAX + 5];

int add(int a,int b,int MOD){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b,int MOD){
    a -= b;

    if(a < 0){
        a += MOD;
    }

    return a;
}

int mult(int a,int b,int MOD){
    return 1LL * a * b % MOD;
}

int lgpow(int base,int exp,int MOD){
    int ans = 1;

    while(exp){

        if(exp & 1){
            ans = 1LL * ans * base % MOD;
        }

        base = 1LL * base * base % MOD;
        exp >>= 1;
    }

    return ans;
}

inline int inv(int val,int MOD){
    return lgpow(val,MOD - 2,MOD);
}

int comb(int n,int k,int MOD){
    return 1LL * fact[n] * (1LL * ifact[n - k] * ifact[k] % MOD) % MOD;
}

int main(){

    fact[0] = 1;

    for(int i = 1;i <= VMAX;i++){
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }

    ifact[VMAX] = lgpow(fact[VMAX],MOD - 2,MOD);

    for(int i = VMAX - 1;i >= 0;i--){
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);
        fr[i % n] += val;
    }

    dp[0][0] = lgpow(2,fr[0],MOD);

    for(int i = 0;i < n - 1;i++){
        for(int k = 0;k < n;k++){
            to[k] = 0;
        }
        int sum = 0;
        for(int k = 0;k <= fr[i + 1];k++){
            to[sum] = add(to[sum],comb(fr[add(i,1,n)],k,MOD),MOD);
            sum = add(sum,add(i,1,n),n);
        }

        for(int j = 0;j < n;j++){
            for(int k = 0;k < n;k++){
                dp[i + 1][k] = add(dp[i + 1][k],mult(dp[i][j],to[scad(k,j,n)],MOD),MOD);
            }
        }
    }

    printf("%d\n",dp[n - 1][0]);

    return 0;
}
