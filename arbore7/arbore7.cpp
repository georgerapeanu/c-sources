#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("arbore7.in","r");
FILE *g = fopen("arbore7.out","w");

const int MOD = 1e9 + 7;
const int NMAX = 1e5;

int n;
int dp[NMAX + 5][2];
int aux[NMAX + 5][2];

vector<int> graph[NMAX + 5];

void dfs(int nod,int tata) {
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
    }

    dp[nod][0] = 0;
    dp[nod][1] = 1;
    aux[nod][0] = 1;
    aux[nod][1] = 1;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }

        dp[nod][0] += max(dp[it][0],dp[it][1]);

        int tmp0 = 0;

        if(dp[it][0] >= dp[it][1]) {
            tmp0 += aux[it][0];
        }
        if(dp[it][0] <= dp[it][1]) {
            tmp0 += aux[it][1];
        }

        aux[nod][0] = 1LL * aux[nod][0] * tmp0 % MOD;

        dp[nod][1] += max(dp[it][0],dp[it][1] - 1);

        int tmp1 = 0;

        if(dp[it][0] >= dp[it][1] - 1) {
            tmp1 += aux[it][0];
        }
        if(dp[it][0] <= dp[it][1] - 1) {
            tmp1 += aux[it][1];
        }

        aux[nod][1] = 1LL * aux[nod][1] * tmp1 % MOD;
    }
}

int main() {

    fscanf(f,"%d",&n);

    for(int i = 1; i < n; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);

    int ans = 0;

    if(dp[1][0] >= dp[1][1]) {
        ans += aux[1][0];
    }
    if(dp[1][0] <= dp[1][1]) {
        ans += aux[1][1];
    }

    ans %= MOD;

    fprintf(g,"%d %d\n",max(dp[1][0],dp[1][1]),ans);

    fclose(f);
    fclose(g);

    return 0;
}
