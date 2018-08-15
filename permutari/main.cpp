#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("perm.in","r");
FILE *g = fopen("perm.out","w");

const int LEN = 100,BASE = 10000;

int N,K;
int dp[205][205][LEN];

void add(int A[],int B[]){
    int t = 0;
    for(int i = 1;i <= A[0] || i <= B[0] || t;i++){
        A[i] = A[i] + B[i] + t;
        t = 0;
        while(A[i] >= BASE){
            A[i] -= BASE;
            t++;
        }
        A[0] = max(A[0],i);
    }
}

void mult(int A[],int val){
    int t = 0;
    for(int i = 1;i <= A[0] || t;i++){
        A[i] = A[i] * val + t;
        t = A[i] / BASE;
        A[i] %= BASE;
        A[0] = max(A[0],i);
    }
}

int main(){

    fscanf(f,"%d %d",&N,&K);

    dp[0][0][0] = dp[0][0][1] = 1;

    for(int i = 1;i <= N;i++){
        for(int j = i;j;j--){
            mult(dp[i - 1][j] , (i - 1));
            add(dp[i][j],dp[i - 1][j]);
            add(dp[i][j],dp[i - 1][j - 1]);
        }
    }

    fprintf(g,"%d",dp[N][K][dp[N][K][0]]);
    for(int i = dp[N][K][0] - 1;i;i--){
        int cb = BASE / 10;
        while(cb > dp[N][K][i] && cb > 1){
            fprintf(g,"0");
            cb /= 10;
        }
        fprintf(g,"%d",dp[N][K][i]);
    }

    fclose(f);
    fclose(g);
    return 0;
}
