#include <cstdio>
#include <cstring>

using namespace std;

FILE *f = fopen("acgt.in","r");
FILE *g = fopen("acgt.out","w");

const int MOD = 666013;

struct matrix_t{
    int n,m;
    int a[10][10];

    matrix_t(){
        n = m = 0;
        memset(a,0,sizeof(a));
    }

    matrix_t(int n,int m){
        this->n = n;
        this->m = m;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                this->a[i][j] = 0;
            }
        }
    }

    matrix_t operator * (const matrix_t &other)const{
        matrix_t ans(this->n,other.m);

        for(int i = 0;i < n;i++){
            for(int j = 0;j < other.m;j++){
                for(int k = 0;k < m;k++){
                    ans.a[i][j] = (ans.a[i][j] + 1LL * this->a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }

        return ans;
    }

    static matrix_t identity(int n){
        matrix_t ans(n,n);

        for(int i = 0;i < n;i++){
            ans.a[i][i] = 1;
        }

        return ans;
    }
};

int n;

matrix_t in;
matrix_t base;
matrix_t out;

matrix_t lgpow(matrix_t base,int e){
    matrix_t ans = matrix_t::identity(base.n);

    while(e){
        if(e & 1){
            ans = ans * base;
        }
        base = base * base;
        e >>= 1;
    }

    return ans;
}

int main(){

    in = matrix_t(4,1);
    in.a[0][0] = 1;
    in.a[1][0] = 1;
    in.a[2][0] = 1;
    in.a[3][0] = 1;

    base = matrix_t(4,4);
    base.a[0][0] = 1;base.a[0][1] = 1;base.a[0][2] = 1;base.a[0][3] = 0;
    base.a[1][0] = 1;base.a[1][1] = 0;base.a[1][2] = 1;base.a[1][3] = 0;
    base.a[2][0] = 1;base.a[2][1] = 1;base.a[2][2] = 0;base.a[2][3] = 0;
    base.a[3][0] = 1;base.a[3][1] = 1;base.a[3][2] = 0;base.a[3][3] = 1;

    fscanf(f,"%d",&n);

    out = lgpow(base,n - 1) * in;

    int ans = (out.a[0][0] + out.a[1][0] + out.a[2][0] + out.a[3][0]) % MOD;

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
