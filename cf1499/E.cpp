#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;
const int MOD = 998244353;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

string x,y;
int dp[NMAX + 1][NMAX + 1][2];

int main(){

    cin >> x;
    cin >> y;

    dp[0][0][0] = 1;
    dp[0][0][1] = 1;

    int ans = 0;
    x = " " + x;
    y = " " + y;

    for(int i = 0;i < (int)x.size();i++){
        for(int j = 0;j < (int)y.size();j++){
            if(i > 0 && (j == 0 || x[i] != y[j])){
                dp[i][j][0] = add(dp[i][j][0],dp[0][j][1]);
            }
            if(j > 0 && (i == 0 || x[i] != y[j])){
                dp[i][j][1] = add(dp[i][j][1],dp[i][0][0]);
            }
            if(i > 0 && i < (int)x.size() - 1){
                dp[i + 1][j][0] = add(dp[i + 1][j][0],add((x[i + 1] != x[i] ? dp[i][j][0]:0),(x[i + 1] != y[j] ? dp[i][j][1]:0)));
            }
            if(j > 0 && j < (int)y.size() - 1){
                dp[i][j + 1][1] = add(dp[i][j + 1][1],add((y[j + 1] != x[i] ? dp[i][j][0]:0),(y[j + 1] != y[j] ? dp[i][j][1]:0)));
            }
            if(i && j){
                ans = add(ans,dp[i][j][0]);
                ans = add(ans,dp[i][j][1]);
            }
        }
    }

    printf("%d\n",ans);


    return 0;
}
