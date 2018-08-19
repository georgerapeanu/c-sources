#include <iostream>
#include <map>
using namespace std;
map<int,int> S;
int fact[int(1e5) + 5];
int ifact[int(1e5) + 5];
int Q,P;
long long LEN;
int PII = 1;
int SZ;
const int MOD = (1e9) + 7;
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
    fact[0] = 1;
    for(int i = 1;i <= (1e5);i++){
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }
    ifact[int(1e5)] = lgpow(fact[int(1e5)],MOD - 2);
    for(int i = (1e5) - 1;i >= 0;i--){
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }
    cin >> Q >> P;
    while(Q--){
        int t,x;
        cin >> t >> x;
        if(t == 0){
            S[x]++;
            PII = 1LL * (1LL * PII * ifact[S[x]] % MOD) * fact[S[x] - 1] % MOD;
            LEN += x;
            SZ++;
        }
        else{
            PII = 1LL * (1LL * PII * fact[S[x]] % MOD) * ifact[S[x] - 1] % MOD;
            S[x]--;
            SZ--;
            LEN -= x;
        }
        if(LEN > P){
            cout << "-1\n";
        }
        else{
            cout << 1LL * (1LL * fact[SZ] * C(P - LEN + (int)SZ,SZ) % MOD) * PII % MOD << "\n";
        }
    }
    return 0;
}
