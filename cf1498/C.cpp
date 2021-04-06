#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000;
const int KMAX = 1000;
const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;

    if(a >= MOD){
        a -= MOD;
    }

    return a;
}


int t;
int n,k;
int dp[KMAX + 5][NMAX + 5][2];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&k);

        for(int i = 0;i <= k;i++){
            for(int j = 0;j <= n + 1;j++){
                dp[i][j][0] = dp[i][j][1] = 0;
            }
            if(i > 0){
                dp[i][0][0] = 1;
                dp[i][n + 1][1] = 1;
            }
        }

        for(int h = 1;h <= k;h++){
            for(int i = 1;i <= n;i++){
                dp[h][i][0] = add(dp[h - 1][i + 1][1],dp[h][i - 1][0]); 
            }
            for(int i = n;i;i--){
                dp[h][i][1] = add(dp[h - 1][i - 1][0],dp[h][i + 1][1]); 
            }
        }

        printf("%d\n",dp[k][1][1]);
    }

     

    return 0;
}
