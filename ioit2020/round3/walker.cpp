#include <cstdio>

using namespace std;

const int MOD = 666013;

int n,k;

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

int lgpow(int b,long long e){
    int ans = 1;

    while(e){
        if(e & 1){
            ans = mult(ans,b);
        }
    
        b = mult(b,b);
        e >>= 1;
    }

    return ans;
}

int ans(int n,long long k){
    if(k == 0){
        return 0;
    }
    if(k == 1){
        return 0;
    }

    if(k % 2 == 0){
        return mult(n - 1,mult(lgpow(n,MOD - 2),add(1,lgpow(n - 1,k - 1))));
    }else{
        return scad(lgpow(n - 1,k - 1),ans(n,k - 1));
    }
}

int main(){

    int n;
    long long k;

    scanf("%d %lld",&n,&k);

    printf("%d\n",ans(n,k));

    return 0;
}
