#include<iostream>

using namespace std;
int dp[100][100];
int N,M;
int main(){
    for(int i = 1;i <= 64;i++){
        for(int j = 0;j <= 65;j++){
            dp[i][j] = 1 << 28;
        }
        for(int j = 1;j <= 65;j++){
            for(int k = 0;k <= i;k++){
                dp[i][j] = min(dp[i][j],dp[k][j] * 2 + dp[i - k][j - 1]);
            }
        }
    }
    cin >> N >> M;
    cout << dp[N][M] << "\n";
    return 0;
}
