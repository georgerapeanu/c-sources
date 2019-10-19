#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int SIGMA = 10;
const int MOD = 1e9 + 7;

int n,m;
int dp[NMAX + 5][2];
string s;

int main(){

    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    cin >> n >> m;
    cin >> s;

    s = " " + s;

    dp[1][0] = 1;
    dp[1][1] = 1;

    for(int i = 2;i <= n;i++){
        dp[i][0] = (9LL * dp[i - 1][0] + dp[i - 1][1]) % MOD;
        dp[i][1] = (8LL * dp[i - 1][0] + dp[i - 1][1]) % MOD;
    }

    for(int i = 1;i <= n;i++){
        for(int j = 0;j < 2;j++){
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }

    while (m--){
        int t,x,y;
        scanf("%d %d %d",&t,&x,&y);

        if(t == 2){
            s[x] = '0' + y;
        }
        else{
            int ans = 0;
            for(int i = x;i <= y;i++){
                if(i > x && s[i - 1] == 1 && s[i] == 3){
                    break;
                }
                if(s[i] > '0'){
                    int coef = 1LL * dp[y - i + 1][0] * (s[i] - '0') % MOD;
                    if(s[i] > '3'){
                        coef = (coef + dp[y - i + 1][1] - dp[y - i + 1][0] + MOD) % MOD;
                    }
                    ans = (ans + coef) % MOD;
                }
                ans += (i == y);
            }
            printf("%d\n",ans);
        }
    }

    return 0;
}

