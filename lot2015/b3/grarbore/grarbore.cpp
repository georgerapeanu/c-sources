#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("grarbore.in","r");
FILE *g = fopen("grarbore.out","w");

const int MOD = 666013;

int t;
int n;

vector<int> graph[505];

int sons[505],len;

int dp[505][505][2];
int pref_dp[505][505];
int dp2[2][505][505];
int pref_dp2[2][505][505];
int mx_gr[505];
int ans[505];

void dfs(int nod,int tata) {

    mx_gr[nod] = graph[nod].size();

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
        mx_gr[nod] = max(mx_gr[nod],mx_gr[it]);
    }

    len = 0;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        sons[++len] = it;
    }

    for(int gr = 0; gr <= mx_gr[nod]; gr++) {
        for(int gr2 = 0; gr2 <= len; gr2++) {
            dp2[0][gr][gr2] = dp2[1][gr][gr2] = 0;
            pref_dp2[0][gr][gr2] = pref_dp2[1][gr][gr2] = 0;
        }
    }

    dp2[0][0][0] = 1;

    for(int gr = 0; gr <= mx_gr[nod]; gr++) {
        pref_dp2[0][gr][0] = 1;
    }

    for(int i = 1; i <= len; i++) {
        for(int gr = 0; gr <= mx_gr[nod]; gr++) {
            for(int gr2 = 0; gr2 <= i; gr2++) {
                dp2[i & 1][gr][gr2] = dp2[(i & 1) ^ 1][gr][gr2];
                if(gr2 > 0) {
                    dp2[i & 1][gr][gr2] =  (dp2[i & 1][gr][gr2] + 1LL * dp2[(i & 1) ^ 1][gr][gr2 - 1] * pref_dp[sons[i]][gr]) % MOD;
                    if(gr > 0) {
                        dp2[i & 1][gr][gr2] =  (dp2[i & 1][gr][gr2] + 1LL * pref_dp2[(i & 1) ^ 1][gr - 1][gr2 - 1] * (dp[sons[i]][gr][0] + dp[sons[i]][gr - 1][1])) % MOD;
                    }
                }
            }
        }
        for(int gr2 = 0; gr2 <= i; gr2++) {
            for(int gr = 0; gr <= mx_gr[nod]; gr++) {
                pref_dp2[i & 1][gr][gr2] = ((gr > 0 ? pref_dp2[i & 1][gr - 1][gr2]:0) + dp2[i & 1][gr][gr2]) % MOD;
            }
        }
    }

    for(int gr = 0; gr <= mx_gr[nod]; gr++) {
        for(int gr2 = 0; gr2 <= len; gr2++) {
            dp[nod][max(gr2,gr)][gr2 >= gr] = (dp[nod][max(gr2,gr)][gr2 >= gr] + dp2[len & 1][gr][gr2]) % MOD;
        }
    }

    pref_dp[nod][0] = dp[nod][0][0];
    for(int gr = 1; gr <= n; gr++) {
        pref_dp[nod][gr] = ((dp[nod][gr][0] + dp[nod][gr - 1][1]) + pref_dp[nod][gr - 1]) % MOD;
    }
}

int main() {

    fscanf(f,"%d",&t);

    while(t--) {
        fscanf(f,"%d",&n);

        for(int i = 1; i <= n; i++) {
            ans[i] = 0;
            graph[i].clear();
        }

        for(int i = 1; i < n; i++) {
            int x,y;
            fscanf(f,"%d %d",&x,&y);
            x++;
            y++;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        dfs(1,0);

        for(int i = 1; i <= n; i++) {
            for(int gr = 1; gr <= n; gr++) {
                ans[gr] = (ans[gr] + dp[i][gr][0] + dp[i][gr][1]) % MOD;
            }
        }

        for(int i = 1; i < n; i++) {
            fprintf(g,"%d ",ans[i]);
        }
        fprintf(g,"\n");

        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= mx_gr[i]; j++) {
                dp[i][j][0] = dp[i][j][1] = 0;
            }
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
