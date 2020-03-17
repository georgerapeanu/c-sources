#include <iostream>

using namespace std;

int n;
int a,b;

const int MOD = 1e9 + 7;

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

int comb(int n,int k){
    int ans = 1;

    for(int i = 0;i < k;i++){
        ans = 1LL * ans * (1LL * (n - i) * lgpow(i + 1,MOD - 2) % MOD) % MOD;
    }

    return ans;
}

int main(){
    cin >> n >> a >> b;

    int ans = lgpow(2,n);
    ans -= comb(n,a);if(ans < 0)ans += MOD;
    ans -= comb(n,b);if(ans < 0)ans += MOD;
    ans -= 1;if(ans < 0)ans += MOD;

    cout << ans;

    return 0;
}
