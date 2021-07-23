#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

///1-indexed
class BipartiteMatcher {
public:

    vector<int> L,R;
    vector< vector<int> > graph;

private:

    vector<bool> viz;
    bool pair_up(int nod) {
        if(viz[nod]) {
            return 0;
        }
        viz[nod] = 1;

        for(auto it:graph[nod]) {
            if(!R[it]) {
                R[it] = nod;
                L[nod] = it;
                return 1;
            }
        }

        for(auto it:graph[nod]) {
            if(pair_up(R[it])) {
                R[it] = nod;
                L[nod] = it;
                return 1;
            }
        }
        return 0;
    }

public:

    BipartiteMatcher(int n,int m) {
        graph.resize(n + 1);
        L.resize(n + 1);
        R.resize(m + 1);
        viz.resize(n + 1);
    }

    void add_edge(int u,int v) {
        graph[u].push_back(v);
    }

    void reset_match() {
        fill(L.begin(),L.end(),0);
        fill(R.begin(),R.end(),0);
        fill(viz.begin(),viz.end(),0);
    }

    void reset_full() {
        fill(L.begin(),L.end(),0);
        fill(R.begin(),R.end(),0);
        fill(viz.begin(),viz.end(),0);
        fill(graph.begin(),graph.end(),vector<int>());
    }

    int max_match() {
        int ans = 0;
        bool ok = 1;
        while(ok) {
            ok = 0;
            fill(viz.begin(),viz.end(),0);
            for(int i = 1; i < (int)L.size(); i++) {
                if(!L[i] && pair_up(i)) {
                    ans++;
                    ok = 1;
                }
            }
        }
        return ans;
    }
};

int n,m;
pair<int,int> edges[20005];
int lvl[3005],len;
vector <int> graph[3005];
int low[3005];
int st[3005];
int viz[3005];
bool inst[3005];
int lastid;
int comp[3005];
int lst_comp;


void ctc(int nod) {
    low[nod] = lvl[nod] = ++lastid;
    viz[nod] = 1;
    st[++len] = nod;
    inst[st[len]] = true;

    for(auto it:graph[nod]) {
        if(!viz[it]) {
            ctc(it);
        }

        if(inst[it]) {
            low[nod] = min(low[nod],low[it]);
        }
    }

    if(low[nod] == lvl[nod]) {
        lst_comp++;
        while(st[len] != nod) {
            comp[st[len]] = lst_comp;
            inst[st[len]] = false;
            len--;
        }
        comp[st[len]] = lst_comp;
        inst[st[len]] = false;
        len--;
    }
}


BipartiteMatcher solver(0,0);

void dfs(int nod,int cul) {
    viz[nod] = cul;
    if(comp[cul - 1] != comp[nod]) {
        solver.add_edge(comp[cul - 1],comp[nod]);
    }
    for(auto it:graph[nod]) {
        if(viz[it] != cul) {
            dfs(it,cul);
        }
    }
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        edges[i] = {x,y};
    }

    for(int i = 1; i <= n; i++) {
        if(viz[i] == 0) {
            ctc(i);
        }
    }

    solver = BipartiteMatcher(lst_comp,lst_comp);

    for(int i = 1; i <= n; i++) {
        dfs(i,i + 1);
    }

    printf("%d\n",lst_comp - solver.max_match());

    return 0;
}
