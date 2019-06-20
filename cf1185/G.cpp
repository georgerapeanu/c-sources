#include <bits/stdc++.h>

using namespace std;

const int NMAX = 50;
const int TMAX = 2500;
const int MOD = 1e9 + 7;

int n,m;
int t[NMAX + 5];
int g[NMAX + 5];

int fr[5];

int dp_first2[2][NMAX + 1][NMAX + 1][TMAX + 1];
int dp_last[2][NMAX + 1][TMAX + 1];
int num_ways[NMAX + 1][NMAX + 1][NMAX + 1][3];

vector<pair<int,int> > genre[2];

inline int total_ways(int i,int j,int k) {
    int ans = 0;
    ans = (ans + num_ways[i][j][k][0]) % MOD;
    ans = (ans + num_ways[i][j][k][1]) % MOD;
    ans = (ans + num_ways[i][j][k][2]) % MOD;
    return ans;
}

int main() {

    scanf("%d %d",&n,&m);

    genre[0] = {{0,0}};
    genre[1] = {{0,0}};

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&t[i],&g[i]);
        genre[g[i] > 2].push_back({t[i],g[i]});
        fr[g[i]]++;
    }

    num_ways[1][0][0][0] = 1;
    num_ways[0][1][0][1] = 1;
    num_ways[0][0][1][2] = 1;

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= n; k++) {
                if(i)num_ways[i][j][k][0] = (num_ways[i][j][k][0] + 1LL * i * (num_ways[i - 1][j][k][1] + num_ways[i - 1][j][k][2])) % MOD;
                if(j)num_ways[i][j][k][1] = (num_ways[i][j][k][1] + 1LL * j * (num_ways[i][j - 1][k][0] + num_ways[i][j - 1][k][2])) % MOD;
                if(k)num_ways[i][j][k][2] = (num_ways[i][j][k][2] + 1LL * k * (num_ways[i][j][k - 1][0] + num_ways[i][j][k - 1][1])) % MOD;
            }
        }
    }
    dp_first2[0][0][0][0] = 1;

    for(int i = 1,l = 1; i < (int)genre[0].size(); i++,l ^= 1) {
        for(int j = 0; j <= i; j++) {
            for(int k = 0; j + k <= i; k++) {
                for(int t = 0; t <= m; t++) {
                    dp_first2[l][j][k][t] = dp_first2[l ^ 1][j][k][t];
                    if(genre[0][i].second == 1) {
                        if(genre[0][i].first <= t && j > 0) {
                            dp_first2[l][j][k][t] = (dp_first2[l][j][k][t] + dp_first2[l ^ 1][j - 1][k][t - genre[0][i].first]) % MOD;
                        }
                    }
                    else {
                        if(genre[0][i].first <= t && k > 0) {
                            dp_first2[l][j][k][t] = (dp_first2[l][j][k][t] + dp_first2[l ^ 1][j][k - 1][t - genre[0][i].first]) % MOD;
                        }
                    }
                }
            }
        }
    }

    dp_last[0][0][0] = 1;

    for(int i = 1,l = 1; i < (int)genre[1].size(); i++,l ^= 1) {
        for(int j = 0; j <= i; j++) {
            for(int t = 0; t <= m; t++) {
                dp_last[l][j][t] = dp_last[l ^ 1][j][t];
                if(j > 0 && genre[1][i].first <= t) {
                    dp_last[l][j][t] = (dp_last[l][j][t] + dp_last[l ^ 1][j - 1][t - genre[1][i].first]) % MOD;
                }
            }
        }
    }

    int l1 = 1 - ((int)genre[0].size() % 2);
    int l2 = 1 - ((int)genre[1].size() % 2);

    int ans = 0;

    for(int t = 0; t <= m; t++) {
        for(int i = 0; i <= fr[1]; i++) {
            for(int j = 0; j <= fr[2]; j++) {
                if(dp_first2[l1][i][j][t] == 0) {
                    continue;
                }
                for(int k = 0; k <= fr[3]; k++) {
                    if(dp_last[l2][k][m - t] == 0) {
                        continue;
                    }
                    ans = (ans + 1LL * (1LL * dp_first2[l1][i][j][t] * dp_last[l2][k][m - t] % MOD) * (total_ways(i,j,k))) % MOD;
                }
            }
        }
    }

    printf("%d\n",ans);

    return 0;
}
