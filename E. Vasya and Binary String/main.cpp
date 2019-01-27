#include <cstdio>
#include <algorithm>

using namespace std;

const long long inf = 1e14;

int n;

char c[105];
int a[105];
long long best[105];

long long dp[105][105];
long long tmp_dp[105][105][105];

int main(){
    scanf("%d\n",&n);

    fgets(c + 1,200,stdin);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        for(int k = 0;k <= i;k++){
            best[i] = max(best[i],a[k] + best[i - k]);
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            for(int k = 1;k <= n;k++){
                tmp_dp[i][j][k] = -inf;
            }
        }
    }

    for(int i = n;i;i--){
        dp[i][i] = best[1];
        tmp_dp[i][i][1] = 0;

        for(int j = i + 1;j <= n;j++){
            for(int k = i;k <= j;k++){
                for(int l = 1;l <= j - i + 1;l++){
                    tmp_dp[j][k][l] = tmp_dp[j - 1][k][l] + (dp[k + 1][j] - dp[k + 1][j - 1]);
                }
            }
            if(c[i] == c[j]){
                for(int k = i;k < j;k++){
                    for(int l = 1;l <= j - i;l++){
                        tmp_dp[j][j][l + 1] = max(tmp_dp[j][j][l + 1],tmp_dp[j - 1][k][l]);
                    }
                }
            }

            for(int k = i;k <= j;k++){
                for(int l = 1;l <= j - i + 1;l++){
                    dp[i][j] = max(dp[i][j],tmp_dp[j][k][l] + best[l]);
                }
            }
        }


        tmp_dp[i][i][1] = -inf;

        for(int j = i + 1;j <= n;j++){
            for(int k = i;k <= j;k++){
                for(int l = 1;l <= j - i + 1;l++){
                    tmp_dp[j][k][l] = -inf;
                }
            }
        }
    }

    printf("%lld",dp[1][n]);

    return 0;
}
