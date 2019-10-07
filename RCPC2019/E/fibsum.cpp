#include <cstdio>

using namespace std;

FILE *f = fopen("fibsum.in","r");
FILE *g = fopen("fibsum.out","w");

const int MOD = 1e9 + 7;

struct matrix_t {
    int n,m;
    int a[10][10];

    matrix_t operator * (const matrix_t &other)const {
        matrix_t ans;
        ans.n = this->n;
        ans.m = other.m;

        for(int i = 1; i <= ans.n; i++) {
            for(int j = 1; j <= ans.m; j++) {
                ans.a[i][j] = 0;
                for(int k = 1; k <= this->m; k++) {
                    ans.a[i][j] = (ans.a[i][j] + 1LL * this->a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }

        return ans;
    }

    matrix_t operator - (const matrix_t &other) {
        matrix_t ans;
        ans.n = this->n;
        ans.m = this->m;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                ans.a[i][j] = (this->a[i][j] - other.a[i][j] + MOD) % MOD;
            }
        }
        return ans;
    }
};

matrix_t lgpow(matrix_t base,int e) {
    matrix_t ans;
    ans.n = ans.m = 2;
    ans.a[1][1] = 1;
    ans.a[1][2] = 0;
    ans.a[2][1] = 0;
    ans.a[2][2] = 1;

    while(e) {
        if(e & 1) {
            ans = ans * base;
        }
        base = base * base;
        e >>= 1;
    }

    return ans;
}

int t;

int main() {

    matrix_t base;
    base.n = 1;
    base.m = 2;
    base.a[1][1] = base.a[1][2] = 1;

    matrix_t fib_base;
    fib_base.n = 2;
    fib_base.m = 2;
    fib_base.a[1][1] = 0;
    fib_base.a[1][2] = 1;
    fib_base.a[2][1] = 1;
    fib_base.a[2][2] = 1;

    fscanf(f,"%d",&t);

    while(t--) {
        int l,r;
        fscanf(f,"%d %d",&l,&r);
        fprintf(g,"%d\n",(base * (lgpow(fib_base,r + 2) - lgpow(fib_base,l + 1))).a[1][1]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
