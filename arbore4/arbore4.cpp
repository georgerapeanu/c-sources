#include <cstdio>
#include <vector>

using namespace std;

FILE *f = fopen("arbore4.in","r");
FILE *g = fopen("arbore4.out","w");

const int NMAX = 1e5;
const int MOD = 666013;

int n;
int dp[NMAX + 5];
int weight[NMAX + 5];
vector<int> graph[NMAX + 5];

int fact[NMAX + 5];
int ifact[NMAX + 5];

int comb(int n,int k) {
    return 1LL * fact[n] * (1LL * ifact[k] * ifact[n - k] % MOD) % MOD;
}

void dfs(int nod,int tata) {
    weight[nod] = 1;
    dp[nod] = 1;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
        dp[nod] = 1LL * (1LL * dp[nod] * dp[it] % MOD) * comb(weight[nod] + weight[it] - 1,weight[it]) % MOD;
        weight[nod] += weight[it];
    }
}

int lgpow(int base,int exp) {
    int p = 1;

    while(exp) {
        if(exp & 1) {
            p = 1LL * p * base % MOD;
        }
        base = 1LL * base * base % MOD;
        exp >>= 1;
    }

    return p;
}

int main() {

    fscanf(f,"%d",&n);

    for(int i = 1; i < n; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    fact[0] = 1;

    for(int i = 1; i <= n; i++) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }

    ifact[n] = lgpow(fact[n],MOD - 2);

    for(int i = n - 1; i >= 0; i--) {
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }

    dfs(1,0);

    fprintf(g,"%d\n",dp[1]);

    fclose(f);
    fclose(g);

    return 0;
}

