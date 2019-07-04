#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("arbore.in","r");
FILE *g = fopen("arbore.out","w");

const int NMAX = 1e5;
const int MMAX = 1e5;
const int VMAX = 1e6;
const int BUCK = 600;

int n,m;
int offset;
int fr[VMAX + 5];
int v[NMAX + 5];

vector<int> graph[NMAX + 5];
int liniarizare[NMAX + 5],last;
int st[NMAX + 5];
int dr[NMAX + 5];

int ans[MMAX + 5];

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

    while(buff[ind] >= '0' && buff[ind] <= '9') {
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

struct query_t {
    int t,p,s;
} q[MMAX + 5];

void dfs(int nod,int tata) {
    liniarizare[++last] = nod;
    st[nod] = last;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
    }

    dr[nod] = last;
}

int main() {

    n = i32();
    m = i32();

    for(int i = 1; i < n; i++) {
        int u,v;
        u = i32();
        v = i32();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 1; i <= m; i++) {
        q[i].t = i32();
        if(q[i].t == 1) {
            q[i].p = i32();
            q[i].s = i32();
        }
        else {
            q[i].s = i32();
        }
    }

    dfs(1,0);

    for(int i = 1; i <= m; i++) {
        ans[i] = -1;
    }

    for(int l = 1; l <= n; l += BUCK) {
        offset = 0;
        int r = min(n,l + BUCK - 1);
        fr[0] = r - l + 1;
        for(int i = 1; i <= m; i++) {
            if(q[i].t == 1) {
                if(st[q[i].p] <= l && r <= dr[q[i].p]) {
                    offset += q[i].s;
                }
                else if(r < st[q[i].p] || l > dr[q[i].p]) {
                    continue;
                }
                else {
                    int ll = max(l,st[q[i].p]);
                    int rr = min(r,dr[q[i].p]);
                    for(int j = ll; j <= rr; j++) {
                        fr[v[j]]--;
                        fr[v[j] += q[i].s]++;
                    }
                }
            }
            else if(ans[i] == -1 && q[i].s >= offset && fr[q[i].s - offset] > 0) {
                for(int j = l; j <= r; j++) {
                    if(v[j] == q[i].s - offset) {
                        ans[i] = liniarizare[j];
                        break;
                    }
                }
            }
        }

        for(int i = l; i <= r; i++) {
            fr[v[i]] = 0;
        }
    }

    for(int i = 1; i <= m; i++) {
        if(q[i].t == 1) {
            continue;
        }
        fprintf(g,"%d\n",ans[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
