#include <cstdio>
using namespace std;
FILE *f = fopen("aiafarapalindroame.in","r");
FILE *g = fopen("aiafarapalindroame.out","w");
int dp1[1000];
int dp2[1000];
int N;
const int MOD = (1e9) + 7;
struct matrix2x2{
    int a[2][2];
    matrix2x2 operator *(const matrix2x2 &other)const{
        matrix2x2 ans;
        for(int i = 0;i < 2;i++){
            for(int j = 0;j < 2;j++){
                ans.a[i][j] = 0;
                for(int k = 0;k < 2;k++){
                    ans.a[i][j] = (1LL * a[i][k] * other.a[k][j] + ans.a[i][j]) % MOD;
                }
            }
        }
        return ans;
    }
};
int main()
{
    fscanf(f,"%d",&N);
    if(N == 1){
        fprintf(g,"%d",26);
    }
    else if(N == 2){
        fprintf(g,"%d",26 * 26);
    }
    else if(N == 3){
        fprintf(g,"%d",26 * 26 * 25);
    }
    else{
        int e = N - 3;
        matrix2x2 I;
        matrix2x2 M;
        M.a[0][0] = 0;
        M.a[0][1] = 1;
        M.a[1][0] = 24;
        M.a[1][1] = 24;
        I.a[0][0] = 1;
        I.a[1][0] = 0;
        I.a[0][1] = 0;
        I.a[1][1] = 1;
        while(e){
            if(e & 1){
                I = I * M;
            }
            M = M * M;
            e >>= 1;
        }
        int rez = ( 1LL * (I.a[0][0] + I.a[1][0]) * 26 * 25 + 1LL * (I.a[0][1] + I.a[1][1]) * 26 * 25 * 25 ) % MOD;
        fprintf(g,"%d",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
