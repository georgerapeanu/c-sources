#include <iostream>

using namespace std;
long long dp[2][10005];
bool pos[2][10005];
long long W,B,X;
int N;
int C[10005];
long long SC[10005];
long long Cost[10005];
long long D[10005],stq,drq;
int main()
{
    cin >> N;
    cin >> W >> B >> X;
    for(int i = 1;i <= N;i++){
        cin >> C[i];
        SC[i] = C[i] + SC[i - 1];
    }
    for(int i = 1;i <= N;i++){
        cin >> Cost[i];
    }
    dp[0][0] = W;
    pos[0][0] = 1;
    for(int i = 1;i <= N;i++){
        stq = 1,drq = 0;
        for(int j = 0;j <= SC[i];j++){
            pos[i & 1][j] = 0;
            while(stq <= drq && j - D[stq] > C[i]){
                stq++;
            }
            if(pos[((i & 1) ^1)][j] == 1){
                while(stq <= drq && min(dp[((i & 1) ^1)][j] + X,W + 1LL * j * B) + 1LL * j * Cost[i] >= min(dp[((i & 1) ^1)][D[drq]] + X,W + 1LL * D[drq] * B) + 1LL * D[drq] * Cost[i]){
                    drq--;
                }
                D[++drq] = j;
            }
            if(stq <= drq){
                dp[i & 1][j] = min(dp[((i & 1) ^1)][D[stq]] + X,W + 1LL * D[stq] * B) + 1LL * D[stq] * Cost[i] - 1LL * j * Cost[i];
                dp[i & 1][j] = min(W + 1LL * j * B,dp[i & 1][j]);
                if(dp[i & 1][j] >= 0){
                    pos[i & 1][j]  = 1;
                }
            }
        }
    }
    int ans = SC[N];
    while(!pos[N & 1][ans]){
        ans--;
    }
    cout << ans;
    return 0;
}
