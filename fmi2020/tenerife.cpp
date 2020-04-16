#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("tenerife.in","r");
FILE *g = fopen("tenerife.out","w");

const int NMAX = 50000;
const int MMAX = 100000;
const int MOD = 1e9 + 7;

vector<pair<int,int> > graph[NMAX + 5];
int n,m,k;
int gr[NMAX + 5];
int topo[NMAX + 5];

int st,dr;

int dp[NMAX + 5];

int solve(int d) {
    for(int i = 1; i <= n; i++) {
        dp[i] = 0;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += dp[topo[i]];
        if(ans >= MOD) {
            ans -= MOD;
        }
        dp[topo[i]]++;
        if(dp[topo[i]] >= MOD) {
            dp[topo[i]] -= MOD;
        }
        for(auto it:graph[topo[i]]) {
            dp[it.first] += dp[topo[i]] * (it.second % d == 0);
            if(dp[it.first] >= MOD) {
                dp[it.first] -= MOD;
            }
        }
    }
    return ans;
}

const int LEN = 1 << 14;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

vector<int> prim;
vector<pair<int,int> > divs;

void get_divs(int pas,pair<int,int> div) {
    if(pas >= (int)prim.size()) {
        divs.push_back(div);
        return ;
    }
    get_divs(pas + 1,div);
    get_divs(pas + 1, {div.first * prim[pas],div.second ^ 1});
}

int main() {

    n = i32();
    m = i32();
    k = i32();

    while(m--) {
        int u,v,c;
        u = i32();
        v = i32();
        c = i32();
        graph[u].push_back({v,c});
        gr[v]++;
    }

    for(int i = 2; 1LL * i * i <= k; i++) {
        if(k % i == 0) {
            prim.push_back(i);
            while(k % i == 0) {
                k /= i;
            }
        }
    }

    if(k != 1) {
        prim.push_back(k);
        k = 1;
    }

    get_divs(0, {1,0});

    st = 1;
    dr = 0;

    for(int i = 1; i <= n; i++) {
        if(gr[i] == 0) {
            topo[++dr] = i;
        }
    }

    while(st <= dr) {
        int nod = topo[st++];

        for(auto it:graph[nod]) {
            gr[it.first]--;
            if(gr[it.first] == 0) {
                topo[++dr] = it.first;
            }
        }
    }

    int ans = 0;

    for(int i = (int)divs.size() - 1; i >= 0; i--) {
        int tmp = solve(divs[i].first);

        if(divs[i].second == 1) {
            ans -= tmp;
            if(ans < 0) {
                ans += MOD;
            }
        }
        else {
            ans += tmp;
            if(ans >= MOD) {
                ans -= MOD;
            }
        }
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
