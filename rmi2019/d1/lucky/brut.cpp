#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int SIGMA = 10;
const int MOD = 1e9 + 7;

int n,m;
int dp[NMAX + 5][SIGMA + 5];
int sdp[NMAX + 5][SIGMA + 5];
string s;

int main(){

    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    cin >> n >> m;
    cin >> s;

    s = " " + s;

    for(int c = 0;c < 10;c++){
        dp[1][c] = 1;
        sdp[1][c] = c + 1;
    }

    for(int i = 2;i <= n;i++){
        for(int c = 0;c < 10;c++){
            dp[i][c] = sdp[i - 1][9];
            if(c == 1){
                dp[i][c] = (MOD + dp[i][c] - dp[i - 1][3]) % MOD;
            }
            sdp[i][c] = (dp[i][c] + (c > 0 ? sdp[i][c - 1]:0)) % MOD;
        }
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
                    ans = (ans + sdp[y - i + 1][s[i] - '0' - 1]) % MOD;
                }
                ans += (i == y);
            }
            printf("%d\n",ans);
        }
    }

    return 0;
}

