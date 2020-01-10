#include <cstdio>
#include <algorithm>

using namespace std;

int n,m;
int dp[305][305];
int cost[10][10][305][305];
int lg2[305];

int get(int x,int y) {
    if(x <= y) {
        return dp[x][y];
    }
    return 0;
}

int get_rmq(int x,int y,int xx,int yy) {
    int lx = lg2[xx - x + 1];
    int ly = lg2[yy -y + 1];
    return max(max(cost[lx][ly][xx][yy],cost[lx][ly][x + (1 << lx) - 1][yy]),
               max(cost[lx][ly][xx][y + (1 << ly) - 1],cost[lx][ly][x + (1 << lx) - 1][y + (1 << ly) - 1]));
}

int main() {

    for(int i = 2; i <= 300; i++)lg2[i] = 1 + lg2[i >> 1];

    freopen("pieaters.in","r",stdin);
    freopen("pieaters.out","w",stdout);

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int c,x,y;
        scanf("%d %d %d",&c,&x,&y);
        cost[0][0][x][y] = c;
    }

    for(int ly = 1; ly <= lg2[n]; ly++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                cost[0][ly][i][j] = max(cost[0][ly - 1][i][j],(j >= (1 << (ly - 1)) ? cost[0][ly - 1][i][j - (1 << (ly - 1))]:0));
            }
        }
    }

    for(int lx = 1; lx <= lg2[n]; lx++) {
        for(int ly = 0; ly <= lg2[n]; ly++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    cost[lx][ly][i][j] = max(cost[lx - 1][ly][i][j],(i >= (1 << (lx - 1)) ? cost[lx - 1][ly][i - (1 << (lx - 1))][j]:0));
                }
            }
        }
    }

    for(int len = 0; len < n; len++) {
        for(int i = 1; i + len <= n; i++) {
            int j = i + len;
            for(int k = i; k <= j; k++) {
                dp[i][j] = max(dp[i][j],get(i,k) + get(k + 1,j));
            }
            for(int k = i; k <= j; k++) {
                dp[i][j] = max(dp[i][j],get(i,k - 1) + get(k + 1,j) + get_rmq(i,k,k,j));
            }
        }
    }

    printf("%d\n",dp[1][n]);

    return 0;
}
