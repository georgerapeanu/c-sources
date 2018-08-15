#include <iostream>

using namespace std;

int dp[305][305];
int SP[305][305];
int C[305][305];
int N,K,M;

int adun(int a,int b){
    a += b;
    if(a >= M){
        a -= M;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % M;
}

int main(){
    cin >> N >> K >> M;

    for(int i = 0;i <= 304;i++){
        C[i][i] = 1;
        C[i][0] = 1;
        for(int j = 1;j < i;j++){
            C[i][j] = adun(C[i - 1][j - 1] , C[i - 1][j]);
        }
    }

    dp[0][0] = 1;
    SP[0][0] = 1;
    for(int k = K;k >= 0;k--){
        dp[1][k] = 1;
        SP[1][k] = adun(SP[1][k + 1] , dp[1][k]);
    }
    for(int i = 2;i <= N + 1;i++){
        for(int j = K;j >= 0;j--){
            for(int k = 1;k < i;k++){
                dp[i][j] = adun(dp[i][j] , mult(dp[i - k][j] , mult(C[i - 2][k - 1] , SP[k][j + 1])));
            }
            SP[i][j] = adun(SP[i][j + 1] , dp[i][j]);
        }
    }

    cout << dp[N + 1][0];
    return 0;
}
