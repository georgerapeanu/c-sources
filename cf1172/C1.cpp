#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int NMAX = 50;

int n,m;

int sgn[NMAX + 5];

int total;
int weight[NMAX + 5];

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

    scanf("%d %d",&n,&m);

    int total = 0;

    for(int i = 1;i <= n;i++){
        scanf("%d",&sgn[i]);
        if(sgn[i] == 0){
            sgn[i]--;
        }
    }
    
    for(int i = 1;i <= n;i++){
        scanf("%d",&weight[i]);
        total += weight[i];
    }

    for(int i = 1; i<= m;i++){
        int nt = 0;
        for(int j = 1;j <= n;j++){
            weight[j] = (weight[j] + 1LL * weight[j] * lgpow(total,MOD - 2) * sgn[j]) % MOD;weight[j] = (weight[j] + MOD) % MOD;
            nt = (nt + weight[j]) % MOD;
        }
        total = nt;
    }

    for(int i = 1;i <= n;i++){
        printf("%d\n",weight[i]);
    }


    return 0;
}
