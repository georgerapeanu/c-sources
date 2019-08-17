#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("palatulvoltaic.in","r");
FILE *g = fopen("palatulvoltaic.ok","w");

const int MOD = 1e9 + 7;
const int NMAX = 3e5;

int n;
int k;
int v[NMAX + 5];
vector<int> graph[NMAX + 5];

int lgpow(int b,int e) {
    int p = 1;
    while(e) {
        if(e & 1) {
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}

int gcd(int a,int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

void dfs(int nod,int tata,int d,int &gg) {
    gg = gcd(gg,v[nod]);
    if(d == 0) {
        return ;
    }
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod,d - 1,gg);
    }
}

int main() {

    fscanf(f,"%d %d",&n,&k);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    for(int i = 1; i < n; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for(int i = 1; i <= n; i++) {
        int ans = 0;
        for(int d = 0; d < n; d++) {
            int gg = k + 1;
            dfs(i,0,d,gg);
            ans = (ans + k + 1 - gg) % MOD;
        }
        ans = 1LL * ans * lgpow(n,MOD - 2) % MOD;
        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
