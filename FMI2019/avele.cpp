#define JUDGE
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("avele.in","r");
FILE *g = fopen("avele.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 1e5;
const int HMAX = 30;
const long long inf = 1LL << 60;

int n,a,b;

int son[2][NMAX + 5];
long long dp[NMAX + 5][HMAX + 5];
int weight[NMAX + 5];

void dfs(int nod) {
    if(!nod) {
        return;
    }
    weight[nod] = 1;

    dfs(son[0][nod]);
    dfs(son[1][nod]);

    int u = son[0][nod];
    int v = son[1][nod];

    weight[nod] += weight[u];
    weight[nod] += weight[v];

    dp[nod][0] = 1LL * weight[nod] * b;
    dp[nod][1] = 1LL * (weight[nod] - 1) * b;

    for(int i = 2; i <= HMAX; i++) {
        dp[nod][i] = inf;
        dp[nod][i] = min(dp[nod][i],dp[u][i - 1] + dp[v][i - 1]);
        dp[nod][i] = min(dp[nod][i],dp[u][i - 1] + dp[v][i - 2]);
        dp[nod][i] = min(dp[nod][i],dp[u][i - 2] + dp[v][i - 1]);
    }
}

int main() {

    fscanf(f,"%d %d %d",&n,&a,&b);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d %d",&son[0][i],&son[1][i]);
    }

    dp[0][0] = 0;
    dp[0][1] = a;

    for(int i = 2; i <= HMAX; i++) {
        dp[0][i] = a + dp[0][i - 1] + dp[0][i - 2];
    }

    dfs(1);

    long long ans = inf;

    for(int i = 0; i <= HMAX; i++) {
        ans = min(ans,dp[1][i]);
    }

    fprintf(g,"%lld",ans);

    return 0;
}
