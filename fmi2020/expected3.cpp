#include <cstdio>

using namespace std;

FILE *f = fopen("expected3.in","r");
FILE *g = fopen("expected3.out","w");

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    int sgn = 1;


    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    if(buff[ind] == '-'){
        sgn *= -1;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans * sgn;
}

long double dp[10][10];

const int MOD = 1e9 + 7;
const int inv2 = MOD / 2 + 1;

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

int main(){
   /* 
    for(int i = 0;i < 10;i++){
        for(int j = 0;j < 10;j++){
            if(i == 0 && j == 0){
                dp[i][j] = 0;
                printf("%.4f ",double(dp[i][j]));
                continue;
            }
            if(i > 0){
                dp[i][j] += i * (dp[i - 1][j] + 1) / ((long double)i + j + 1);
            }
            if(j > 0){
                dp[i][j] += j * (dp[i][j - 1]) / ((long double)i + j + 1);
            }
            printf("%.4f ",double(dp[i][j]));
        }
        printf("\n");
    }
*/

    int n,m,a,b;

    n = i32();
    m = i32();
    a = i32();
    b = i32();

    fprintf(g,"%d\n",scad(mult(a,mult(n,inv2)),mult(b,mult(m,inv2))));

    fclose(f);
    fclose(g);

    return 0;
}
