#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int lgpow(int b,long long e){
    int p = 1;

    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        e >>= 1;
        b = 1LL * b * b % MOD;
    }

    return p;
}

struct matrix_t{
    int n,m;
    int a[10][10];

    matrix_t(int n,int m){
        this->n = n;
        this->m = m;
        memset(a,0,sizeof(a));
    }

    matrix_t operator * (const matrix_t &other)const{
        matrix_t ans(this->n,other.m);
        for(int i = 1;i <= this->n;i++){
            for(int j = 1;j <= other.m;j++){
                ans.a[i][j] = 0;
                for(int k = 1;k <= this->m;k++){
                    ans.a[i][j] = (ans.a[i][j] + 1LL * this->a[i][k] * other.a[k][j]) % (MOD - 1);
                }
            }
        }
        return ans;
    }
};

matrix_t matrix_lgpow(matrix_t b,long long e){
    matrix_t p(b.n,b.m);
    for(int i = 1;i <= b.n;i++){
        p.a[i][i] = 1;
    }

    while(e){
        if(e & 1){
            p = p * b;
        }
        b = b * b;
        e >>= 1;
    }

    return p;
}

int main(){

    long long n;
    int f1,f2,f3,c;

    cin >> n >> f1 >> f2 >> f3 >> c;

    matrix_t a_raise(3,3);
    a_raise.a[1][1] = 1;a_raise.a[1][2] = 1;a_raise.a[1][3] = 1;
    a_raise.a[2][1] = 1;
    a_raise.a[3][2] = 1;

    a_raise = matrix_lgpow(a_raise,n - 3);
    
    matrix_t c_raise(5,5);
    c_raise.a[1][1] = 1;
    c_raise.a[2][1] = 2;c_raise.a[2][2] = 1;
    c_raise.a[3][2] = 1;c_raise.a[3][3] = 1;c_raise.a[3][4] = 1;c_raise.a[3][5] = 1;
    c_raise.a[4][3] = 1;
    c_raise.a[5][4] = 1;

    c_raise = matrix_lgpow(c_raise,n - 3);

    matrix_t c_init(5,1);
    c_init.a[1][1] = 1;
    c_init.a[2][1] = 2;

    int c_exp = (c_raise * c_init).a[3][1];
    
    matrix_t a_init(3,3);

    a_init.a[1][1] = 1;
    a_init.a[2][2] = 1;
    a_init.a[3][3] = 1;

    matrix_t a = a_raise * a_init;

    int f3_exp = a.a[1][1];
    int f2_exp = a.a[1][2];
    int f1_exp = a.a[1][3];

    int ans = 1;

    ans = 1LL * ans * lgpow(c,c_exp) % MOD;
    ans = 1LL * ans * lgpow(f1,f1_exp) % MOD;
    ans = 1LL * ans * lgpow(f2,f2_exp) % MOD;
    ans = 1LL * ans * lgpow(f3,f3_exp) % MOD;

    cout << ans << " ";

    return 0;
}
