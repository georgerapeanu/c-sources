#include <cstdio>

using namespace std;

FILE *f = fopen("margiki.in","r");
FILE *g = fopen("margiki.out","w");

const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;    
}

struct matrix_t{
    int n,m;
    int a[10][10];

    matrix_t(int n,int m){
        this->n = n;
        this->m = m;

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                a[i][j] = 0;
            }
        }
    }

    matrix_t operator * (const matrix_t &other)const{
        matrix_t ans(this->n,other.m);

        for(int i = 1;i <= this->n;i++){
            for(int j = 1;j <= other.m;j++){
                ans.a[i][j] = 0;
                for(int k = 1;k <= this->m;k++){
                    ans.a[i][j] = add(ans.a[i][j],mult(this->a[i][k],other.a[k][j]));
                }
            }
        }
        return ans;
    }
};

matrix_t identity(int n){
    matrix_t ans(n,n); 
    for(int i = 1;i <= n;i++){
        ans.a[i][i] = 1;
    }
    return ans;
}

matrix_t lgpow(matrix_t base,long long e){

    matrix_t p = identity(base.n);

    while(e){
        if(e & 1){
            p = p * base;
        }
        base = base * base;
        e >>= 1;
    }

    return p;
}

int main(){
    
    matrix_t init(3,1);
    init.a[1][1] = 1;
    init.a[2][1] = 1;
    init.a[3][1] = 2;

    matrix_t base(3,3);

    base.a[1][2] = 1;
    base.a[2][3] = 1;
    base.a[3][1] = base.a[3][2] = base.a[3][3] = 1;

    long long n;
    fscanf(f,"%lld",&n);

    if(n <= 2){
        fprintf(g,"%d\n",init.a[1][n + 1]);
        return 0;
    }

    init = lgpow(base,n - 2) * init;

    fprintf(g,"%d\n",init.a[3][1]);

    fclose(f);
    fclose(g);

    return 0;
}
