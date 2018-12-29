#include <iostream>

using namespace std;

const int MOD = 998244353;

int dp[105][5005];

int lgpow(int b,int e){
    int p = 1;
    while(e){
        if(e & 1){
            p = 1LL * b * p % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}

int comb(int n,int k){
    int ans = 1,base = 1;
    for(int i = n - k + 1;i <= n;i++){
        ans = 1LL * ans * i % MOD;
    }

    for(int i = 1;i <= k;i++){
        base = 1LL * base * i % MOD;    
    }

    return 1LL * ans * lgpow(base,MOD - 2) % MOD;
}

int main(){
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    
    int p,s,r;

    cin >> p >> s >> r;
    
    dp[0][0] = 1;

    for(int i = 1;i <= p;i++){
        for(int j = 0;j <= s;j++){
            dp[i][j] = dp[i - 1][j];
            if(j){
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
            if(j >= r){
                dp[i][j] = (dp[i][j] - dp[i - 1][j - r] + MOD) % MOD;
            }
        }
    }

    int ans = lgpow(p,MOD - 2);
    ans = 1LL * ans * (comb(s + p - 1,p - 1) - dp[p][s] + MOD) % MOD;
    ans = 1LL * ans * lgpow(comb(s - r + p - 1,p - 1),MOD - 2) % MOD;
    cout << ans;

    return 0;
}
