#include <iostream>

using namespace std;

const int MOD = (1e9) + 7;

long long lgpow(long long b,long long e){
    long long p = 1;
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
    long long x,k;
    cin >> x >> k;
    if(k == 0){
        cout << 2 * x % MOD;
        return 0;
    }
    if(x == 0){
        cout << 0;
        return 0;
    }
    x %= MOD;
    long long ans = x * lgpow(2,k + 1) - lgpow(2,k) + 1;
    ans = ans % MOD;
    if(ans < 0)ans += MOD;
    cout << ans;
    return 0;
}
