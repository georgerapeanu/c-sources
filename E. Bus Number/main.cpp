#include <iostream>

using namespace std;

string S;
int fr[10];
unsigned long long dp[11][20];
unsigned long long C[40][40];
int main(){
    for(int i = 0;i < 20;i++){
        C[i][0] = 1;
        for(int j = 1;j <= i;j++){
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }

    cin >> S;
    for(auto it:S){
        fr[it - '0']++;
    }
    dp[0][0] = 1;
    for(int cf = 1;cf <= 9;cf++){
        for(int i = 0;i <= 19;i++){
            for(int j = (fr[10 - cf] > 0);j <= fr[10 - cf];j++){
                if(i >= j){
                    dp[cf][i] += dp[cf - 1][i - j] * C[i][j];
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 1;i <= 19;i++){
        for(int j = (fr[0] > 0);j <= fr[0];j++){
            if(i > j){
                dp[10][i] += dp[9][i - j] * C[i - 1][j];
            }
        }
        ans += dp[10][i];
    }
    cout << ans;
    return 0;
}
