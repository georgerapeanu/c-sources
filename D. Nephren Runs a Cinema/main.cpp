#include <iostream>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
long long P[12],phi,nrp;
long long N,MOD,l,r;
void setMod(long long MOD){
    phi = MOD;nrp = 0;
    for(long long i = 2;1LL * i * i <= MOD;i++){
        if(MOD % i == 0){
            phi = (phi / i) * (i - 1);
            P[++nrp] = i;
            while(MOD % P[nrp] == 0){
                MOD /= P[nrp];
            }
        }
    }
    if(MOD != 1){
        P[++nrp] = MOD;
        phi = phi / MOD * (MOD - 1);
    }
}
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
struct Integer{
    long long E[12];
    long long val;
    void init(long long x){
        for(long long i = 0;i < 12;i++){
            E[i] = 0;
        }
        for(long long i = 1;i <= nrp;i++){
            E[i] = 0;
            while(x % P[i] == 0){
                x /= P[i];
                E[i]++;
            }
        }
        val = x;
    }
    Integer operator *(const Integer &other)const{
        Integer ans;
        for(long long i = 0;i < 12;i++){
            ans.E[i] = 0;
        }
        for(long long i = 1;i <= nrp;i++){
            ans.E[i] = E[i] + other.E[i];
        }
        ans.val = (1LL * val * other.val) % MOD;
        return ans;
    }
    Integer operator /(const Integer &other)const{
        Integer ans;
        for(long long i = 0;i < 12;i++){
            ans.E[i] = 0;
        }
        for(long long i = 1;i <= nrp;i++){
            ans.E[i] = E[i] - other.E[i];
        }
        ans.val = (1LL * val * lgpow(other.val,phi - 1)) % MOD;
        return ans;
    }
    long long toInt(){
        long long rez = val;
        for(long long i = 1;i <= nrp;i++){
            rez = 1LL * rez * lgpow(P[i],E[i]) % MOD;
        }
        return rez;
    }
};
Integer lgpow2(Integer b,long long e){
    Integer p;p.init(1);
    while(e){
        if(e & 1){
            p = p * b;
        }
        b = b * b;
        e >>= 1;
    }
    return p;
}
Integer fact[100005];
Integer ifact[100005];
long long C(long long N,long long K){
    if(K < 0 || K > N){
        return 0;
    }
    return (fact[N] * ifact[K] * ifact[N - K]).toInt();
}
long long rez = 0;
int main()
{
    cin >> N >> MOD >> l >> r;
    setMod(MOD);
    fact[0].init(1);
    for(long long i = 1;i <= N;i++){
        Integer tmp;tmp.init(i);
        fact[i] = fact[i - 1] * tmp;
    }
    Integer tmp;tmp.init(1);
    ifact[N] = tmp / fact[N];
    for(long long i = N - 1;i >= 0;i--){
        Integer tmp;tmp.init(i + 1);
        ifact[i] = ifact[i + 1] * tmp;
    }
    for(long long nonvip = l;nonvip <= N;nonvip++){
        long long tmpans = C(N,nonvip);
        swap(N,nonvip);
        tmpans = ( (long long)tmpans * ( (C(N,(N - l) / 2) - C(N,(N - r + 1) / 2 - 1) + MOD) % MOD ) ) % MOD;
        swap(N,nonvip);
        rez = (rez + tmpans) % MOD;
    }
    cout << rez;
    return 0;
}
