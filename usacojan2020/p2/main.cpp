#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
const int INV2 = 500000004;

struct matrix_t{
    ///0 is for void kinda
    int a[21][21];

    matrix_t(){
        memset(a,0,sizeof(a));
    }

    matrix_t operator * (const matrix_t &other){
        matrix_t ans;
        for(int i = 0;i < 21;i++){
            for(int k = i; k < 21;k++){
                if(a[i][k] == 0){
                    continue;
                }
                for(int j = k;j < 21;j++){
                    ans.a[i][j] = (1LL * this->a[i][k] * other.a[k][j] + ans.a[i][j]) % MOD;
                }
            }
        }
        return ans;
    }

    void stationary_setup(int val){
        memset(a,0,sizeof(a));
        a[0][0] = 1;///void;
        a[val][val] = 1;///val sequence;
    }

    void transition_setup(int val){
        for(int i = 0;i < 21;i++){
            a[i][i]++;
        }
        for(int j = 0;j <= val;j++){
            a[j][val]++;
        }
    }

    void transition_inverse_setup(int val){
        for(int i = 0;i < 21;i++){
            a[i][i]++;
        }
        for(int j = 0;j <= val;j++){
            a[j][val] += MOD - INV2;
        }
    }

    int sum(){
        int ans = 0;

        for(int i = 0;i < 21;i++){
            for(int j = i;j < 21;j++){
                ans = (ans + a[i][j]) % MOD;
            }
        }
        return ans;
    }

    matrix_t only_row(const matrix_t &other,int val){
        matrix_t ans;
        for(int i = val;i <= val;i++){
            for(int j = 0; j < 21;j++){
                for(int k = i;k <= j;k++){
                    ans.a[i][j] = (1LL * this->a[i][k] * other.a[k][j] + ans.a[i][j]) % MOD;
                }
            }
        }
        return ans;
    }

    int get_mult_sum(const matrix_t &other){
        int ans = 0;
        for(int i = 0;i < 21;i++){
            int sum_c = 0;
            int sum_l = 0;
            for(int j = 0;j < 21;j++){
                sum_c += a[j][i];
                sum_l += other.a[i][j];
                if(sum_c >= MOD)sum_c -= MOD;
                if(sum_l >= MOD)sum_l -= MOD;
            }
            ans = (1LL * sum_c * sum_l + ans) % MOD;
        }
        return ans;
    }

    void afis(){
        for(int i = 0;i <= 20;i++){
            for(int j = 0;j <= 20;j++){
                printf("%d ",a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
};

FILE *f = fopen("nondec.in","r");
FILE *g = fopen("nondec.out","w");

int n;
int q,k;
int v[50005];
matrix_t trans[50005];
matrix_t i_trans[50005];

int main(){

    fscanf(f,"%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i]);
        trans[i].transition_setup(v[i]);
        i_trans[i].transition_inverse_setup(v[i]);
        if(i > 1){
            trans[i] = trans[i - 1] * trans[i];
            i_trans[i] = i_trans[i] * i_trans[i - 1];
        }
    }

    fscanf(f,"%d",&q);

    while(q--){
        int l,r;
        fscanf(f,"%d %d",&l,&r);
        int sum = (i_trans[l].only_row(trans[r],0).sum() + i_trans[l].only_row(trans[r],v[l]).sum());
        fprintf(g,"%d\n",sum);
    }

    fclose(f);
    fclose(g);

    return 0;
}
