#include "fiboxor.h"

const int LGMAX = 60;
const int KMAX = 20;
const int MOD = (1 << KMAX) - 1;

struct matrix_t {
    int n,m;
    int a[3][3];

    matrix_t() {
        ;
    }

    matrix_t(int n,int m) {
        this->n = n;
        this->m = m;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                a[i][j] = 0;
            }
        }
    }

    matrix_t operator * (const matrix_t &other)const {
        matrix_t ans(this->n,other.m);

        for(int i = 1; i <= this->n; i++) {
            for(int j = 1; j <= other.m; j++) {
                ans.a[i][j] = 0;
                for(int k = 1; k <= this->m; k++) {
                    ans.a[i][j] = (ans.a[i][j] + (1LL * this->a[i][k] * other.a[k][j]) & MOD);
                }
            }
        }

        return ans;
    }

};

matrix_t pw2[LGMAX + 1];

int get_fibonacci(long long i) {


    matrix_t ans(2,2);
    ans.a[1][1] = 1;
    ans.a[1][2] = 0;
    ans.a[2][1] = 0;
    ans.a[2][2] = 1;

    for(int h = 0; h <= LGMAX; h++) {
        if((i >> h) & 1) {
            ans = ans * pw2[h];
        }
    }

    return ans.a[1][2];
}

void init(int q) {

    pw2[0] = matrix_t(2,2);
    pw2[0].a[1][1] = 0;
    pw2[0].a[1][2] = 1;
    pw2[0].a[2][1] = 1;
    pw2[0].a[2][2] = 1;

    for(int i = 1; i <= LGMAX; i++) {
        pw2[i] = pw2[i - 1] * pw2[i - 1];
    }

}

int query(int k,long long l,long long r) {

    long long a = get_fibonacci(l);
    long long b = get_fibonacci(l + 1);

    int ans = 0;

    while(l <= r) {
        ans ^= a;
        l++;
        long long c = ((a + b) & MOD);
        a = b;
        b = c;
    }

    return (ans & ((1 << k) - 1));
}
