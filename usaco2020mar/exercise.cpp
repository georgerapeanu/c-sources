#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};

FastMod F(2);

int gcd(int a,int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

int lcm(int a,int b) {
    return a * b / gcd(a,b);
}

int lgpow(int b,int e) {
    int p = 1;

    while(e) {
        if(e & 1) {
            p = F.reduce(1LL * p * b);
        }
        b = F.reduce(1LL * b * b);
        e >>= 1;
    }

    return p;
}

int n,m;

int fact[7505];
int ifact[7505];
int dp[7505][7505];
int suml[7505];
int sumc[7505];

vector<int> divs[7505];

int arang(int n,int k) {
    return F.reduce(1LL * fact[n] * ifact[n - k]);
}

int main() {

    for(int i = 1; i <= 7500; i++) {
        for(int j = i; j <= 7500; j += i) {
            divs[j].push_back(i);
        }
    }

    scanf("%d %d",&n,&m);
    F = FastMod(m);

    fact[0] = 1;

    for(int i = 1; i <= 7500; i++) {
        fact[i] = F.reduce(1LL * i * fact[i - 1]);
    }

    ifact[7500] = lgpow(fact[7500],m - 2);

    for(int i = 7500 - 1; i >= 0; i--) {
        ifact[i] = F.reduce(1LL * (i + 1) * ifact[i + 1]);
    }

    dp[0][1] = 1;
    sumc[1] = 1;
    suml[0] = 1;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {

            for(int k = 1; k <= i; k++) {
                dp[i][j] = (dp[i][j] + 1LL * ifact[i - k] * dp[i - k][j]) % m;
                if(k % j == 0) {
                    dp[i][j] = F.reduce(dp[i][j] + 1LL * ifact[i - k] * fact[i - k]);
                    dp[i][j] = (dp[i][j] - 1LL * ifact[i - k] * dp[i - k][j]) % m;
                }
                else {
                    dp[i][j] = F.reduce(dp[i][j] + 1LL * ifact[i - k] * dp[i - k][j]);
                }
            }
            dp[i][j] = F.reduce(1LL * fact[i - 1] * dp[i][j]);

            /*        dp[i][j] = sumc[j];
                    for(int k = j;k <= i;k += j){
                        dp[i][j] = F.reduce(dp[i][j] - 1LL * dp[i - k][j] * ifact[i - k]);
                        dp[i][j] = F.reduce(dp[i][j] + 1LL * fact[i - k] * ifact[i - k]);
                    }
                    dp[i][j] = F.reduce(1LL * fact[i - 1] * dp[i][j]);
                    sumc[j] = F.reduce(sumc[j] + 1LL * dp[i][j] * ifact[i]);
                    suml[i] = F.reduce(suml[i] + 1LL * dp[i][j] * ifact[i]);*/
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }


    return 0;
}
