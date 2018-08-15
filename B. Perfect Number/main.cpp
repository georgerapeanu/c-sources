#include <iostream>
#include <cstdio>
using namespace std;
const int LIM = 1e5;
int dp[105][11];
int K;
void solve(int K){
    int pos;
    for(int i = 1; i <= 100;i++){
        if(dp[i][10] >= K){
            pos = i;
            break;
        }
    }
    int x = pos,y = 10;
    while(x){
        for(int cf = 0;cf <= 9 && cf <= y;cf++){
            if(dp[x - 1][y - cf] >= K){
                x--;
                y-=cf;
                cout << cf;
                break;
            }
            else{
                K -= dp[x - 1][y - cf];
            }
        }
    }
    cout << "\n";
}
int main()
{
   /// freopen("out","w",stdout);
    dp[0][0] = 1;
    for(int i = 1;i <= 100;i++){
        for(int j = 0;j <= 10;j++){
            for(int cf = 0;cf <= j && cf <= 9;cf++){
                dp[i][j] += dp[i - 1][j - cf];
                dp[i][j] = min(dp[i][j],LIM);
            }
        }
    }
    cin >> K;
    solve(K);
    return 0;
}
