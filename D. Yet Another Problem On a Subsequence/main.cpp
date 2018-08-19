#include <iostream>

using namespace std;

const int MOD = 998244353;

int C[1005][1005];
int N;
int A[1005];
int dp[1005];
int SP[1005];

int main(){

    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
    }

    for(int i = 0;i <= N;i++){
        C[i][0] = 1;
        for(int j = 1;j <= i;j++){
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if(C[i][j] >= MOD){
                C[i][j] -= MOD;
            }
        }
    }

    dp[0] = 1;
    SP[0] = 1;

    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= i;j++){
            if(A[j] > 0 && i - j - 1 >= A[j] - 1){
                dp[i] = (dp[i] + 1LL * SP[j - 1] * C[i - j - 1][A[j] - 1]) % MOD;
            }
        }
        SP[i] = SP[i - 1] + dp[i];
        if(SP[i] >= MOD){
            SP[i] -= MOD;
        }
    }

    cout << SP[N] - 1;

    return 0;
}
