#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("shoturi.in","r");
FILE *g = fopen("shoturi.out","w");

const int NMAX = 5000;
const int KMAX = 20000;
const int MOD = 269696969;

pair<int,int> delta[KMAX + 5];
int dp[2][KMAX + 5];

int n,k;
int h[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&k);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&h[i]);
    }

    for(int i = 1,l = 1; i <= n; i++,l ^= 1) {
        pair<int,int> pula = {0,0};
        delta[0] = {h[i],0};
        for(int j = 0; j <= k; j++) {
            pula.second += pula.first;
            pula.second %= MOD;
            pula.second += delta[j].second;
            pula.second %= MOD;
            pula.first += delta[j].first;
            pula.first %= MOD;
            delta[j] = {0,0};
            dp[l][j] = dp[l][j] + pula.second;
            dp[l][j] %= MOD;
        }
        for(int j = 0; j <= k; j++) {
            delta[j].first += 1LL * dp[l][j] * h[i + 1] % MOD;
            delta[j].first %= MOD;
            delta[j].second += 0;
            dp[l ^ 1][j] = dp[l][j];
        }
    }

    fprintf(g,"%d\n",dp[n & 1][k]);

    fclose(f);
    fclose(g);

    return 0;
}
