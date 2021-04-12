#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct edge_t{
    int u,v,flow,cap;
    edge_t(){
        u = 0;
        v = 0;
        flow = 0;
        cap = 0;
    }
};

const int NMAX = 1e5;
FILE *f = fopen("tarnacop.in","r");
FILE *g = fopen("tarnacop.out","w");

int n,m,s,d;
vector<int> graph[NMAX + 5];
vector<edge_t> edges;
int last_id;
int low[NMAX + 5];
int id[NMAX + 5];
bool inst[NMAX + 5];
int st[NMAX + 5];
int len;
int ctc[NMAX + 5];
int last_comp;

void dfs(int nod){
    st[++len] = nod;
    inst[nod] = true;
    low[nod] = id[nod] = ++last_id;

    for(auto it:graph[nod]){
        if(id[it] == 0){
            dfs(it);
        }
        if(inst[it]){
            low[nod] = min(low[it],low[nod]);
        }
    }

    if(low[nod] == id[nod]){
        last_comp++;
        while(st[len] != nod){
            ctc[st[len]] = last_comp;
            inst[st[len]] = false;
            len--;
        }
        ctc[st[len]] = last_comp;
        inst[st[len]] = false;
        len--;
    }
}

int main(){

    fscanf(f,"%d %d %d %d",&n,&m,&s,&d);

    for(int i = 1;i <= m;i++){
        edges.push_back(edge_t());
        fscanf(f,"%d %d %d %d",&edges.back().u,&edges.back().v,&edges.back().cap,&edges.back().flow);
        if(edges.back().flow > 0){
            graph[edges.back().v].push_back(edges.back().u);
        }
        if(edges.back().flow < edges.back().cap){
            graph[edges.back().u].push_back(edges.back().v);
        }
    }

    for(int i = 1;i <= n;i++){
        if(id[i] == 0){
            dfs(i);
        }
    }

    vector<pair<int,int> > ans;

    for(int i = 0;i < m;i++){
        if(edges[i].flow == edges[i].cap && edges[i].cap > 0 && ctc[edges[i].u] != ctc[edges[i].v]){
            ans.push_back({edges[i].u,edges[i].v});
        }
    }

    sort(ans.begin(),ans.end());

    fprintf(g,"%d\n",(int)ans.size());
    for(auto &it:ans){
        fprintf(g,"%d %d\n",it.first,it.second);
    }

    fclose(f);
    fclose(g);

    return 0;
}

