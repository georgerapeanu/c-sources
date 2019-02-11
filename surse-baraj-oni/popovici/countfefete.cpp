#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = (int) 1e9 + 7;
const int MAXN = (int) 2e5;

vector <int> g[MAXN + 1];
int v[MAXN + 1], p2[MAXN + 1];

inline void mod(int &x) {
    if(x < 0)
        x += MOD;
    if(x >= MOD)
        x -= MOD;
}

int cnt0, cnt1;

void dfs(int nod, int p, int bit, int id) {
    if(v[nod] < v[id] || (v[nod] == v[id] && nod < id))
        return ;
    if(v[nod] & (1 << bit))
        cnt1++;
    else
        cnt0++;
    for(auto it : g[nod]) {
        if(it != p)
            dfs(it, nod, bit, id);
    }
}

inline int get(int x0, int x1, int bit) {
    if(x1 + x0 == 0)
        return 0;
    if(bit == 0) {
        if(x1 == 0)
            return p2[x0] - 1;
        if(x0 == 0)
            return p2[x1 - 1] - 1;
        return p2[x1 - 1 + x0] - 1;
    }
    else {
        if(x1 == 0)
            return 0;
        return p2[x1 - 1 + x0];
    }
}

int main() {
    FILE *fi, *fout;
    int i, n, x, y;
    fi = fopen("countfefete.in" ,"r");
    fout = fopen("countfefete.out" ,"w");
    fscanf(fi,"%d " ,&n);
    int mx = 0;
    p2[0] = 1;
    for(i = 1; i <= n; i++) {
        fscanf(fi,"%d " ,&v[i]);
        p2[i] = p2[i - 1] * 2;
        mod(p2[i]);
        if(v[i] > mx)
            mx = v[i];
    }
    for(i = 1; i < n; i++) {
        fscanf(fi,"%d %d " ,&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int ans = 0;
    for(int bit = 0; bit < 30; bit++) {
        if((1 << bit) > mx)
            continue;
        for(i = 1; i <= n; i++) {
            int nr = 0, tot1 = 0, tot0 = 0;
            int sz = g[i].size();
            for(int pos = 0; pos < sz; pos++) {
                int it = g[i][pos];
                cnt0 = cnt1 = 0;
                dfs(it, i, bit, i);
                tot1 += cnt1;
                tot0 += cnt0;
                if(v[i] & (1 << bit)) {
                    nr -= get(cnt0, cnt1, 0);
                }
                else {
                    nr -= get(cnt0, cnt1, 1);
                }
                mod(nr);
            }
            if(v[i] & (1 << bit))
                tot1++;
            else
                tot0++;
            if(v[i] & (1 << bit)) {
                nr += get(tot0, tot1, 0);
            }
            else {
                nr += get(tot0, tot1, 1);
            }
            mod(nr);
            ans = (ans + 1LL * nr * (1 << bit)) % MOD;
        }
    }
    fprintf(fout,"%d" ,ans);
    fclose(fi);
    fclose(fout);
    return 0;
}
