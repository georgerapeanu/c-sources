#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

int n;

int fact[NMAX + 5];
int ifact[NMAX + 5];
int fr[10];

int real_ans = 0;

void btr(int pas,long long sum,long long prod,long long cnt){
    if(pas > 9){
        if(prod != sum || cnt < n){
            return ;
        }

        int ans = 0;

        for(int i = 1;i <= 9;i++){
            ans += fr[i];
        }

        ans = fact[ans];

        for(int i = 1;i <= 9;i++){
            ans = 1LL * ans * ifact[fr[i]] % MOD;
        }
        
        real_ans += ans;
        if(real_ans >= MOD){
            real_ans -= MOD;
        }

        return;
    }

    if(pas == 1){
        sum = max(n - 20,0);
    }

    for(int i = (pas == 1 ? max(n - 20,0):0);cnt + i <= n;i++){
        if(prod > sum && prod * pas > sum + pas){
            break;
        }
        fr[pas] = i;
        btr(pas + 1,sum,prod,cnt + i);
        fr[pas] = 0;
        prod *= pas;
        sum += pas;
    }
}

int lgpow(int base,int exp){
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

int main(){

    scanf("%d",&n);

    if(n == 1){
        printf("10\n");
        return 0;
    }

    fact[0] = 1;

    for(int i = 1;i <= n;i++){
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }

    ifact[n] = lgpow(fact[n],MOD - 2);

    for(int i = n - 1;i >= 0;i--){
        ifact[i] = 1LL * (i + 1) * ifact[i + 1] % MOD;
    }

    btr(1,0,1,0);

    printf("%d\n",real_ans);

    return 0;
}
