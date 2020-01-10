#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("turism.in","r");
FILE *g = fopen("turism.out","w");

const int NMAX = 3e4;

int n,m;
int gr[NMAX + 5];
vector<int> graph[NMAX + 5];

struct dsu_t {
    int dsu[NMAX + 5];
    int sz[NMAX + 5];

    dsu_t(int n) {
        for(int i = 1; i <= n; i++) {
            dsu[i] = 0;
            sz[i] = 0;
        }
    }

    int fi_root(int x) {
        if(dsu[x] == 0) {
            return x;
        }
        return dsu[x] = fi_root(dsu[x]);
    }

    bool unite(int x,int y) {
        x = fi_root(x);
        y = fi_root(y);
        if(x == y) {
            return false;
        }
        dsu[x] = y;
        sz[y] += sz[x];
        return true;
    }

    int& get_sz(int x) {
        return sz[fi_root(x)];
    }
};


int main() {

    fscanf(f,"%d %d",&n,&m);

    dsu_t dsu(n);

    for(int i = 1; i <= m; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        dsu.unite(x,y);
        gr[x]--;
        gr[y]++;
    }

    for(int i = 1; i <= n; i++) {
        dsu.get_sz(i) += max(0,gr[i]);
    }

    vector<int> in,out;

    for(int i = 1; i <= n; i++) {
        if(dsu.get_sz(i) == 0) {
            dsu.get_sz(i)++;
            in.push_back(i);
            out.push_back(i);
        }
        else {
            for(int j = 1; j <= gr[i]; j++) {
                out.push_back(i);
            }
            for(int j = 1; j <= -gr[i]; j++) {
                in.push_back(i);
            }
        }
    }

    fprintf(g,"%d\n",(int)in.size());

    for(int i = 0; i < (int)out.size(); i++) {
        if(i < (int)out.size() - 1 && dsu.fi_root(out[i]) == dsu.fi_root(in[i]) && dsu.get_sz(out[i]) == 1) {
            swap(in[i],in[i + 1]);
        }
        dsu.unite(out[i],in[i]);
        fprintf(g,"%d %d\n",out[i],in[i]);
        dsu.get_sz(out[i])--;
    }


    fclose(f);
    fclose(g);

    return 0;
}
