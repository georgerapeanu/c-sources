#include <cstdio>

using namespace std;

const int VMAX = (1 << 20);
const int MOD = 1e9 + 7;

int n;
int sgn[VMAX + 5];
int dp[VMAX + 5];
int pw[VMAX + 5];

int add(int a,int b) {
    a += b;
    if(a >= MOD) {
        a -= MOD;
    }

    return a;
}

int scad(int a,int b) {
    a -= b;
    if(a < 0) {
        a += MOD;
    }

    return a;
}

int main() {

    pw[0] = 1;

    for(int i = 1; i <= VMAX; i++) {
        pw[i] = add(pw[i - 1],pw[i - 1]);
    }

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        dp[val]++;
    }

    for(int i = 0; i <= 20; i++) {
        for(int x = 0; x <= VMAX; x++) {
            if(((x >> i) & 1) == 0) {
                dp[x] += dp[x ^ (1 << i)];
            }
        }
    }

    sgn[0] = 1;

    for(int x = 0; x <= VMAX; x++) {
        sgn[x] = sgn[x / 2] * (x % 2 == 1 ? -1:1);
    }

    int ans = 0;

    for(int i = 0; i <= VMAX; i++) {
        pw[i] = scad(pw[i],1);
    }

    for(int x = 0; x <= VMAX; x++) {
        if(sgn[x] == 1) {
            ans = add(ans,pw[dp[x]]);
        }
        else {
            ans = scad(ans,pw[dp[x]]);
        }
    }

    printf("%d\n",ans);

    return 0;
}
