#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int conf[] = {
    10,
    2,
    9,
    7,
    18,
    21,
    12,
    3,
    29,
    23
};

struct matrix_t {
    int n,m;
    int a[105][105];

    matrix_t() {
        memset(a,0,sizeof(a));
    }

    matrix_t(int n,int m) {
        this->n = n;
        this->m = m;
        memset(a,0,sizeof(a));
    }

    matrix_t operator * (const matrix_t &other) const {
        matrix_t ans(this->n,other.m);

        for(int i = 0;i < ans.n;i++){
            for(int j = 0;j < ans.m;j++){
                ans.a[i][j] = 0;
                for(int k = 0;k < m;k++){
                    ans.a[i][j] = (ans.a[i][j] + 1LL * a[i][k] * other.a[k][j]) % MOD;
                }
            }
        } 

        return ans;
    }

    void afis(){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                printf("%d ",a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
};

matrix_t lgpow(matrix_t base,long long exp) {
    matrix_t ans(base.n,base.m);

    for(int i = 0;i < ans.n;i++) {
        for(int j = 0;j < ans.m;j++) {
            ans.a[i][j] = (i == j);
        }
    }

    while(exp) {
        if(exp & 1) {
            ans = ans * base;
        }
        base = base * base;
        exp >>= 1;
    }

    return ans;
}

long long n,k;
int m,x;
int comb[105][105];

int lgpow_num(int b,long long e){
    int p = 1;

    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }

    return p;
}

int get_conf(int val){
    if(m == 1){
        return conf[val];
    }
    if(m == 2){
        return conf[val % 10] | (conf[val / 10] << 5);
    }
}

matrix_t get_matrix(long long k,matrix_t base) {
    matrix_t vec(base.m,1);
    vec.a[0][0] = 1;
    matrix_t tmp = lgpow(base,k) * vec;

    matrix_t ans((m == 1 ? 10:100),(m == 1 ? 10:100));

    for(int i = 0;i < ans.n;i++){
        for(int j = 0;j < ans.m;j++){
            int bit_diff = __builtin_popcount(get_conf(i) ^ get_conf(j));
            ans.a[i][j] = 1LL * tmp.a[bit_diff][0] * 
            lgpow_num(comb[m * 5][bit_diff],MOD - 2) % MOD;
        }
    }

    return ans;
}

int main() {

    for(int i = 0;i <= 100;i++) {
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1;j < i;j++) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }

    scanf("%d %lld %lld %d",&m,&n,&k,&x);

    matrix_t base(m * 5 + 1,m * 5 + 1);

    for(int i = 0;i <= m * 5;i++){
        if(i > 0){
            base.a[i][i - 1] = m * 5 - (i - 1);
        }
        if(i < m * 5){
            base.a[i][i + 1] = (i + 1);
        }
    }

    matrix_t dp = lgpow(get_matrix(k,base),n / k) * get_matrix(n % k,base); 

    for(int i = 0;i < (m == 1 ? 10:100);i++) {
        printf("%d\n",dp.a[x][i]);
    }

    return 0;
}
