#include <cstdio>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 100;

struct matrix_t {
    int n,m;
    int a[NMAX + 5][NMAX + 5];

    matrix_t(int n = 101,int m = 101) {
        this->n = n;
        this->m = m;
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                this->a[i][j] = 0;
            }
        }
    }

    matrix_t operator *(const matrix_t &other) {
        matrix_t ans(this->n,other.m);

        for(int i = 1; i <= this->n; i++) {
            for(int j = 1; j <= other.m; j++) {
                for(int k = 1; k <= this->m; k++) {
                    ans.a[i][j] = (ans.a[i][j] + 1LL * this->a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }

        return ans;
    }
};

int n,x;

int fr[200];

matrix_t lgpow(matrix_t base,int e) {
    matrix_t ans(base.n,base.m);

    for(int i = 1; i <= ans.n; i++) {
        ans.a[i][i] = 1;
    }

    while(e) {
        if(e & 1) {
            ans = ans * base;
        }
        base = base * base;
        e >>= 1;
    }

    return ans;
}

int main() {

    scanf("%d %d",&n,&x);

    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d",&x);
        fr[x]++;
    }

    matrix_t base(101,1);
    matrix_t delta(101,101);

    base.a[100][1] = 1;
    base.a[101][1] = 1;

    for(int i = 1; i < 100; i++) {
        delta.a[i][i + 1] = 1;
    }

    for(int j = 1; j <= 100; j++) {
        delta.a[100][j] = fr[100 - j + 1];
        delta.a[101][j] = fr[100 - j + 1];
    }

    delta.a[101][101] = 1;

    delta = lgpow(delta,x);

    base = delta * base;

    printf("%d\n",base.a[101][1]);

    return 0;
}
