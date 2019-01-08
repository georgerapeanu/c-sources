#include <cstdio>
#include <vector>

using namespace std;

const int LIM = 50;
const int MOD = 1e9 + 7;
const int KMAX = 1e4;

inline int add(int a,int b) {
    a += b;
    if(a >= MOD) {
        a -= MOD;
    }
    return a;
}

inline int mult(int a,int b) {
    return 1LL * a * b % MOD;
}

int lgpow(int b,int e) {
    int p = 1;
    while(e) {
        if(e & 1) {
            p = 1LL * b * p % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}

struct matrix_t {
    int n,m;
    int a[LIM + 5][LIM + 5];

    matrix_t() {
        this->n = LIM + 5;
        this->m = LIM + 5;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                a[i][j] = 0;
            }
        }
    }

    matrix_t operator * (const matrix_t &other)const {
        matrix_t ans;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < other.m; j++) {
                ans.a[i][j] = 0;
                for(int k = 0; k < m; k++) {
                    ans.a[i][j] = add(ans.a[i][j],mult(this->a[i][k],other.a[k][j]));
                }
            }
        }
        return ans;
    }
};

long long n;
int k;
int inv[LIM + 5];

vector< pair<long long,int> > v;

matrix_t dp[LIM + 5];
matrix_t base[LIM + 5];
matrix_t change[LIM + 5];

void btr(int pas,int prod,int prob,int &ans) {
    if(pas >= (int)v.size()) {
        ans = add(ans,mult(prob,prod));
        return ;
    }

    for(int i = 0; i <= (int)v[pas].second; i++) {
        btr(pas + 1,prod,mult(prob,dp[v[pas].second].a[v[pas].second - i][0]),ans);
        prod = mult(prod,v[pas].first);
    }
}

matrix_t lgpow_mat(matrix_t b,int e) {
    matrix_t p;

    for(int i = 0; i < b.n; i++) {
        p.a[i][i] = 1;
    }

    while(e) {
        if(e & 1) {
            p = p * b;
        }
        b = b * b;
        e >>= 1;
    }

    return p;
}

int main() {

    for(int i = 1; i <= LIM; i++) {
        inv[i] = lgpow(i,MOD - 2);
    }

    scanf("%lld %d",&n,&k);

    int total = 0;

    for(int i = 2; 1LL * i * i <= n; i++) {
        if(n % i == 0) {
            v.push_back({i,0});
            while(n % i == 0) {
                v.back().second++;
                n /= i;
                total++;
            }
        }
    }

    if(n != 1) {
        v.push_back({n % MOD,1});
        total++;
    }

    for(int i = 0; i <= total; i++) {
        base[i].a[0][0] = 1;
        for(int j = 0; j <= i; j++) {
            for(int k = 0; k <= j; k++) {
                change[i].a[j][k] = inv[i - k + 1];
            }
        }
        change[i] = lgpow_mat(change[i],k);
        dp[i] = change[i] * base[i];
    }

    int ans = 0;

    btr(0,1,1,ans);

    printf("%d",ans);


    return 0;
}
