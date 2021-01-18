#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 3000;
const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;

    if(a >= MOD){
        a -= MOD;
    }

    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

int n;
pair<int,int> v[2 * NMAX + 5];
int dp[2 * NMAX + 1][NMAX + 1][2];

int main(){
    
    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i].first);
        v[i].second = 0;
    }
    
    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i + n].first);
        v[i + n].second = 1;
    }

    sort(v + 1,v + 1 + 2 * n);

    dp[0][0][0] = 1;

    for(int i = 1;i <= 2 * n;i++){
        for(int j = 0;j <= n;j++){
            if(v[i].second == 0){
                if(j > 0){
                    dp[i][j][0] = add(dp[i][j][0],dp[i - 1][j - 1][0]);
                }
                dp[i][j][1] = add(dp[i][j][1],dp[i - 1][j][0]);
                dp[i][j][1] = add(dp[i][j][1],dp[i - 1][j][1]);
                if(j > 0){
                    dp[i][j][1] = add(dp[i][j][1],dp[i - 1][j - 1][1]);
                }
            }else{
                dp[i][j][0] = add(dp[i][j][0],mult(j + 1,dp[i - 1][j + 1][0]));
                dp[i][j][0] = add(dp[i][j][0],dp[i - 1][j][0]);
                dp[i][j][1] = add(dp[i][j][1],mult(j + 1,dp[i - 1][j + 1][1]));
            }
        }
    }

    printf("%d\n",add(dp[2 * n][0][1],dp[2 * n][0][0]));


    return 0;
}
