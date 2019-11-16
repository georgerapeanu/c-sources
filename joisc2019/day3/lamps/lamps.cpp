#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 1e6;
const int inf = 1e9;

int n;
string s;
string t;
int dp[NMAX + 5][3][2];

void trans(int i,int j,int k,int ii,int jj,int kk) {
    if(i != ii - 1) {
        return ;
    }

    if(jj == 0) {
        if(s[ii] - '0' != ((t[ii] - '0') ^ kk)) {
            return ;
        }
        dp[ii][jj][kk] = min(dp[ii][jj][kk],dp[i][j][k] + (k == 0 && kk == 1));
        return ;
    }

    if(t[ii] - '0' != ((jj - 1) ^ kk)) {
        return ;
    }

    dp[ii][jj][kk] = min(dp[ii][jj][kk],dp[i][j][k] + (k == 0 && kk == 1) + (j != jj));
}

int main() {

    cin >> n;
    cin >> s;
    cin >> t;

    s = " " + s;
    t = " " + t;

    dp[0][0][1] = inf;
    dp[0][1][0] = inf;
    dp[0][1][1] = inf;
    dp[0][2][0] = inf;
    dp[0][2][1] = inf;

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 2; k++) {
                dp[i][j][k] = inf;
                for(int jj = 0; jj < 3; jj++) {
                    for(int kk = 0; kk < 2; kk++) {
                        trans(i - 1,jj,kk,i,j,k);
                    }
                }
            }
        }
    }

    int ans = inf;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 2; j++) {
            ans = min(ans,dp[n][i][j]);
        }
    }

    printf("%d\n",ans);

    return 0;
}
