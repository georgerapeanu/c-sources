#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("pandemie.in","r");
FILE *g = fopen("pandemie.out","w");

const int NMAX = 120000;
const int LGMAX = 17;

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

int aint[4 * NMAX + 5];

int n,q;
int len;
int st[NMAX + 5];
int dr[NMAX + 5];
int invlin[NMAX + 5];

bool active[NMAX + 5];

vector<int> graph[NMAX + 5];
int lvl[NMAX + 5];
int fa[LGMAX + 1][NMAX + 1];

void dfs(int nod,int tata) {
    fa[0][nod] = tata;
    st[nod] = ++len;
    invlin[len] = nod;
    lvl[nod] = 1 + lvl[tata];
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
    }
    dr[nod] = len;
}

void update(int nod,int st,int dr,int pos,int val) {
    if(dr < pos || st > pos) {
        return;
    }

    if(st == dr) {
        aint[nod] = val;
        return;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
}

int query(int nod,int st,int dr,int l,int r,int pos) {
    if(r < st || dr < l || aint[nod] < pos) {
        return 1;
    }
    int mid = (st + dr) / 2;
    if(l <= st && dr <= r) {
        if(st == dr) {
            return st;
        }
        if(aint[nod * 2 + 1] >= pos) {
            return query(nod * 2 + 1,mid + 1,dr,l,r,pos);
        }
        else {
            return query(nod * 2,st,mid,l,r,pos);
        }
    }
    return max(query(nod * 2,st,mid,l,r,pos),query(nod * 2 + 1,mid + 1,dr,l,r,pos));
}

int main() {

    n = i32();

    for(int i = 1; i < n; i++) {
        int u,v;
        u = i32();
        v = i32();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,0);

    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 1; i <= n; i++) {
            fa[h][i] = fa[h - 1][fa[h - 1][i]];
        }
    }

    q = i32();

    while(q--) {
        int t,x;
        t = i32();
        x = i32();
        if(t == 1) {
            update(1,1,n,st[x],dr[x]);
            active[x] = 1;
        }
        else if(t == 2) {
            update(1,1,n,st[x],0);
            active[x] = 0;
        }
        else {
            int node = invlin[query(1,1,n,1,st[x],st[x])];

            if(active[node] == false) {
                node = fa[0][node];
            }

            for(int h = LGMAX; h >= 0; h--) {
                if(lvl[fa[h][x]] > lvl[node]) {
                    x = fa[h][x];
                }
            }
            fprintf(g,"%d\n",x);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
