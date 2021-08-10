#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int NMAX = 2e5;
const int VMAX = 2e5;

const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }

    return p;
}

int n;
int p[VMAX + 5];
bool is_not_prime[VMAX + 5];
int mobius[VMAX + 5];
int fr[VMAX + 5];

int main(){

    for(int i = 0;i <= VMAX;i++){
        p[i] = 1;
        mobius[i] = 1;
    }

    is_not_prime[0] = is_not_prime[1] = true;
    mobius[0] = 0;
    mobius[1] = 1;

    for(int i = 2;i <= VMAX;i++){
        if(is_not_prime[i] == false){
            for(int j = i;j <= VMAX;j += i){
                mobius[j] *= -1;
                is_not_prime[j] = true;
            }
            for(long long j = 1LL * i * i;j <= VMAX;j += 1LL * i * i){
                mobius[j] = 0;
            }
        }
    }


    scanf("%d",&n);


    for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);
        fr[val]++;
    }

    for(int i = 1;i <= VMAX;i++){
        fr[i] = add(fr[i - 1],fr[i]);
    }

    int ans = 0;
    for(int i = 1;i <= VMAX;i++){
        if(mobius[i] != 0){
            int coef = 1;

            for(int j = i,k = 1;j <= VMAX;j += i,k++){
                int cnt = fr[min(VMAX,j + i - 1)] - fr[j - 1];
                coef = mult(coef,lgpow(k,cnt));
            }
            if(mobius[i] == 1){
                ans = add(ans,coef);
            }else{
                ans = scad(ans,coef);
            }
        }
        if(fr[i]){
            break;
        }
    }


    printf("%d\n",ans);

    return 0;
}
