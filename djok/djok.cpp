#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("djok.in","r");
FILE *g = fopen("djok.out","w");

const int NMAX = 150000;

int n,k;
int cost[NMAX + 5];
vector<int> graph[NMAX + 5];
bool ins[NMAX + 5];

struct dsu_t {
    int father;
    int weight;
    int latest_node;

    dsu_t(int father = 0,int weight = 1,int latest_node = 0) {
        this->father = father;
        this->weight = weight;
        this->latest_node = latest_node;
    }

} dsu[NMAX + 5];

int fi_root(int nod) {
    if(dsu[nod].father == 0) {
        return nod;
    }

    return dsu[nod].father = fi_root(dsu[nod].father);
}

bool unite(int u,int v,int last) {
    u = fi_root(u);
    v = fi_root(v);

    if(u == v) {
        return false;
    }

    if(dsu[u].weight > dsu[v].weight) {
        swap(u,v);
    }

    dsu[u].father = v;
    dsu[v].weight += dsu[u].weight;
    dsu[v].latest_node = last;

    return true;
}

int father[NMAX + 5];
int ans[NMAX + 5];

pair<int,int> get_ans(int nod) {
    if(father[nod] == 0) {
        return {ans[nod],nod};
    }
    pair<int,int> tmp = get_ans(father[nod]);
    father[nod] = tmp.second;
    return tmp;
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

    while(buff[ind] >= '0' && buff[ind] <= '9') {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int main() {

    n = i32();
    k = i32();

    vector<pair<int,int> > tmp;

    for(int i = 1; i <= n; i++) {
        cost[i] = i32();
        tmp.push_back({cost[i],i});
        dsu[i] = dsu_t(0,1,i);
    }

    for(int i = 1; i < n; i++) {
        int u,v;
        u = i32();
        v = i32();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    sort(tmp.begin(),tmp.end());

    for(int i = 0; i < (int)tmp.size(); i++) {
        ins[tmp[i].second] = true;
        for(auto it:graph[tmp[i].second]) {
            if(ins[it] == true) {
                if(cost[dsu[fi_root(it)].latest_node] + k >= tmp[i].first) {
                    father[dsu[fi_root(it)].latest_node] = tmp[i].second;
                }
                unite(tmp[i].second,it,tmp[i].second);
            }
        }
        ans[tmp[i].second] = dsu[fi_root(tmp[i].second)].weight;
    }

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",get_ans(i).first);
    }

    fclose(f);
    fclose(g);

    return 0;
}
