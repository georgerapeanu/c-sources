#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;


struct matrix_t {
    int n,m;
    int a[3][3];

    matrix_t(int n,int m) {
        this->n = n;
        this->m = m;
        memset(a,0,sizeof(a));
    }

    matrix_t operator * (const matrix_t &other)const {
        matrix_t ans(n,other.m);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < other.m; j++) {
                ans.a[i][j] = 0;
                for(int k = 0; k < m; k++) {
                    ans.a[i][j] = (ans.a[i][j] + 1LL * this->a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }
        return ans;
    }
};

matrix_t lgpow(matrix_t b,long long e) {
    matrix_t p(2,2);
    p.a[0][0] = 1;
    p.a[0][1] = 0;
    p.a[1][0] = 0;
    p.a[1][1] = 1;

    while(e) {
        if(e & 1) {
            p = p * b;
        }
        b = b * b;
        e >>= 1;
    }

    return p;
}

int n,m,l,r;

int main() {

    scanf("%d %d %d %d",&n,&m,&l,&r);

    int even = (r - l + 1) / 2;
    int odd = (r - l + 1) / 2;

    if((r - l + 1) & 1) {
        if(r % 2) {
            odd++;
        }
        else {
            even++;
        }
    }

    matrix_t ans(2,2);
    ans.a[0][0] = even;
    ans.a[0][1] = odd;
    ans.a[1][0] = odd;
    ans.a[1][1] = even;

    ans = lgpow(ans,1LL * n * m);

    int real_ans = 0;

    if((n % 2) && (m % 2)) {
        for(int i = 0; i < 2; i++) {
            real_ans = (real_ans + ans.a[i][0]) % MOD;
        }
    }
    else {
        real_ans = ans.a[0][0];
    }

    printf("%d\n",real_ans);

    return 0;
}
