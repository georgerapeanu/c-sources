#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int m;
long double p;

long double lgpow(long double b,long long e){
    long double p = 1;

    while(e){
        if(e & 1){
            p *= b;
        }
        b *= b;
        e >>= 1;
    }

    return p;
}

long double Exp(long long x){
    return (1LL * n * x + m) / (1 - lgpow(1 - p,x));
}

int main(){

    scanf("%d",&t);

    while(t--){
        int tmp;
        scanf("%d %d %d",&n,&m,&tmp);
        p = tmp / ((long double)10000);

        long long ans = 0;

        for(int jump = 1 << 30;jump;jump >>= 1){
            if(Exp(ans + jump) > Exp(ans + jump + 1)){
                ans += jump;
            }
        }
        printf("%.6f\n",(double)Exp(ans + 1));
    }


    return 0;
}
