#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
long long K,N,A,B,ans;
int fact[300005];
int ifact[300005];

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

int C(int N,int K){
    return 1LL * (1LL * fact[N] * ifact[K] % MOD) * ifact[N - K] % MOD;
}

int main(){
    cin >> N >> A >> B >> K;

    fact[0] = 1;

    for(int i = 1;i <= N;i++){
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }

    ifact[N] = lgpow(fact[N],MOD - 2);

    for(int i = N - 1;i >= 0;i--){
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }

    for(long long numA = 0;numA <= N;numA++){
        long long scoreA = A * numA;
        long long scoreB = K - scoreA;
        if(scoreB >= 0 && scoreB % B == 0 &&scoreB <= N * B){
            long long numB = scoreB / B;
            ans = (ans + 1LL * C(N,numA) * C(N,numB)) % MOD;
        }
    }

    cout << ans;

    return 0;
}
