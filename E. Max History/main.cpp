#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
const int MOD = (1e9) + 7;
int dp[1000005];
int nr[1000005];
int N;
int V[1000005];
int adun(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}
int mult(int a,int b){
    return 1LL * a * b % MOD;
}
int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}
int fac[1000005];
int sfact[1000005];
int lst[1000005];
int fact(int N){
    if(N <= 1){
        fac[N] = 1;
        sfact[N] = sfact[N - 1] + fac[N];
        return fac[N];
    }
    fac[N] = mult(N,fact(N - 1));
    sfact[N] = sfact[N - 1] + fac[N];
    return fac[N];
}
map<int,int> fr;
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
int sumofarang(int n){
    int tmp = 1,rez = 0;
    for(int i = 0;i <= n;i++){
        rez += mult(tmp,fac[N - i - 1]);
        cerr << mult(tmp,fac[N - i - 1]) << "\n";
        tmp *= (n - i);
    }
    return rez;
}
int tmp[1000005];
int main()
{
    nr[0] = 1;
    scanf("%d",&N);
    for(int i  = 1;i <= N;i++){
        scanf("%d",&V[i]);
        fr[V[i]]++;
    }
    sort(V + 1,V + 1 + N);
    fact(N);
    fac[0] = 1;sfact[0] = 1;
    nr[0] = 1;
    int last = 0,rez = 0;
    for(int i  = 1;i <= N;i++){
            tmp[i] = mult(fac[N - i],fac[i - 1]);
            if(i){
                tmp[i] = adun(tmp[i - 1],tmp[i]);
            }
    }
    for(int i = 1;i <= N;i = last){
        last = i;
        while(V[last] == V[i]){
            last++;
        }
        if(V[i] == V[N]){
            break;
        }
        rez = adun(rez,mult(mult(fac[N],mult(last - i,lgpow(N - i + 1,MOD - 2))),V[i]));
    }
    printf("%d",rez);
    return 0;
}
