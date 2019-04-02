#include "wombats.h"
#include <queue>
#include <algorithm>

using namespace std;

int n,m;
int h[5000][200];
int v[5000][200];

int dp[5000][200];

int sum = 0;

void init(int R, int C, int H[5000][200], int V[5000][200]) {
    n = R;
    m = C;

    for(int i = 0;i < R;i++){
        for(int j = 0; j < C;j++){
            h[i][j] = H[i][j];
            v[i][j] = V[i][j];
            sum += h[i][j];
            sum += v[i][j];
        }
    }
}

void changeH(int P, int Q, int W) {
    sum += W - h[P][Q];
    h[P][Q] = W;
}

void changeV(int P, int Q, int W) {
    sum += W - v[P][Q];
    v[P][Q] = W;
}

int escape(int V1, int V2) {
    if(m == 1){
        return sum;
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            dp[i][j] = 1 << 28;
        }
    }        

    dp[0][V1] = 0;

    for(int i = V1 - 1;i >= 0;i--){
        dp[0][i] = dp[0][i + 1] + h[0][i];
    }

    for(int i = V1 + 1;i < m;i++){
        dp[0][i] = dp[0][i - 1] + h[0][i - 1];
    }

    for(int i = 1;i < n;i++){
        queue< pair<int,int> > q;
        for(int j = 0;j < m;j++){
            dp[i][j] = dp[i - 1][j] + v[i - 1][j];
            q.push({j,dp[i][j]});
        }

        while(!q.empty()){
            int x = q.front().first;
            int cost = q.front().second;
            q.pop();

            if(x > 0 && dp[i][x - 1] > dp[i][x] + h[i][x - 1]){
                dp[i][x - 1] = dp[i][x] + h[i][x - 1];
                q.push({x - 1,dp[i][x - 1]});
            }

            if(x + 1 < m && dp[i][x + 1] > dp[i][x] + h[i][x]){
                dp[i][x + 1] = dp[i][x] + h[i][x];
                q.push({x + 1,dp[i][x + 1]});
            }
        }
    }

    return dp[n - 1][V2];
}
