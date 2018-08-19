#include <iostream>
#include <algorithm>

using namespace std;

const int inf = 303 * 1e6;

int N,M;
int V[305];
int dp[305][305][2];

void up(int &target,int val){
    target = min(target,val);
}

int main(){
    cin >> N >> M;

    bool z = 0;

    for(int i = 1;i <= N;i++){
        cin >> V[i];
        z |= (V[i] == 0);
    }

    if(!z){
        V[++N] = 0;
    }

    sort(V + 1,V + 1 + N);

    int st = 0;

    for(int i = 1;i <= N;i++){
        if(!V[i]){
            st = i;
        }
        dp[i][i][0] = dp[i][i][1] = inf;
    }

    int ans = 0;

    for(int k = 1;k <= N;k++){
        dp[st][st][0] = dp[st][st][1] = 0;
        for(int l = 2;l <= k;l++){
            for(int i = 1;i <= N - l + 1;i++){
                int j = i + l - 1;
                int coef = k - l + 1;
                dp[i][j][0] = inf;
                dp[i][j][1] = inf;
                up(dp[i][j][0],dp[i + 1][j][0] + coef * abs(V[i] - V[i + 1]));
                up(dp[i][j][0],dp[i + 1][j][1] + coef * abs(V[i] - V[j]));
                up(dp[i][j][0],dp[i][j - 1][0] + coef * abs(V[j] - V[i]) + coef * abs(V[j] - V[i]));
                up(dp[i][j][0],dp[i][j - 1][1] + coef * abs(V[j] - V[i]) + coef * abs(V[j] - V[j - 1]));

                up(dp[i][j][1],dp[i + 1][j][0] + coef * abs(V[j] - V[i]) + coef * abs(V[i + 1] - V[i]));
                up(dp[i][j][1],dp[i + 1][j][1] + coef * abs(V[j] - V[i]) + coef * (V[j] - V[i]));
                up(dp[i][j][1],dp[i][j - 1][0] + coef * abs(V[j] - V[i]));
                up(dp[i][j][1],dp[i][j - 1][1] + coef * abs(V[j] - V[j - 1]));
            }
        }

        for(int i = 1;i <= N - k + 1;i++){
            int j = i + k - 1;
            ans = max(ans,M * k - dp[i][j][0]);
            ans = max(ans,M * k - dp[i][j][1]);
        }
    }

    cout << ans - M * (!z);

    return 0;
}
