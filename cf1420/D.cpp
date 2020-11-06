#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;
const int MOD = 998244353;

int fact[NMAX + 5];
int ifact[NMAX + 5];

int n,k;
int cnt;
vector<pair<int,int> > events;

int comb(int n,int k){
    if(k < 0 || k > n){
        return 0;
    }
    return 1LL * fact[n] * (1LL * ifact[k] * ifact[n - k] % MOD) % MOD;
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
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }

    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);

    for(int i = NMAX - 1;i >= 0;i--){
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }

    scanf("%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        events.push_back({l,1});
        events.push_back({r + 1,-1});
    }

    sort(events.begin(),events.end());

    int ans = 0;

    cnt = 0;
    for(auto it:events){
        if(it.second == 1){
            ans = (ans + comb(cnt,k - 1)) % MOD;
        }
        cnt += it.second;
    }

    printf("%d\n",ans);

    return 0;
}
