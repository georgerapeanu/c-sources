#include <cstdio>

using namespace std;

int lgpow(int b,int e,int mod) {
    int p = 1;
    while(e) {
        if(e & 1) {
            p = 1LL * p * b % mod;
        }
        e >>= 1;
        b = 1LL * b * b % mod;
    }
    return p;
}

int main() {
    int n;
    scanf("%d",&n);
    if(n == 4) {
        printf("YES\n1\n3\n2\n4\n");
        return 0;
    }
    int p = 1;
    for(int i = 1; i <= (n - 1); i++) {
        p = 1LL * p * i % n;
    }
    if(p == 0) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n1\n");

    for(int i = 2; i < n; i++) {
        printf("%lld\n",1LL * i * lgpow(i - 1,n - 2,n) % n);
    }

    if(n > 1)printf("%d\n",n);
    return 0;
}
