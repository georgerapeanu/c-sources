#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
 
using namespace std;
 
FILE *f = fopen("minmaxtree.in","r");
FILE *g = fopen("minmaxtree.out","w");
 
struct query_t{
    bool type;
    int u,v,val;
     
    void read(){
        char c;
        fscanf(f,"%c %d %d %d\n",&c,&u,&v,&val);
        type = (c == 'm');
    }
};
 
class BipartiteMatcher{
public:
 
    vector<int> L,R;
    vector< vector<int> > graph;
 
private:
 
    vector<bool> viz;
    bool pair_up(int nod){
        if(viz[nod]){
            return 0;
        }
        viz[nod] = 1;
         
        for(auto it:graph[nod]){
            if(!R[it]){
                R[it] = nod;
                L[nod] = it;
                return 1;
            }
        }
         
        for(auto it:graph[nod]){
            if(pair_up(R[it])){
                R[it] = nod;
                L[nod] = it;
                return 1;
            }
        }
        return 0;
    }
     
public:
 
    BipartiteMatcher(int n,int m){
        graph.resize(n + 1);
        L.resize(n + 1);
        R.resize(m + 1);
        viz.resize(n + 1);
    }
     
    void add_edge(int u,int v){
        graph[u].push_back(v);
    }
     
    int max_match(){
        int ans = 0;
        bool ok = 1;
        fill(L.begin(),L.end(),0);
        fill(R.begin(),R.end(),0);
        while(ok){
            ok = 0;
            fill(viz.begin(),viz.end(),0);
            for(int i = 1;i < (int)L.size();i++){
                if(!L[i] && pair_up(i)){
                    ans++;
                    ok = 1;
                }
            }
        }
        return ans;
    }
};
 
const int NMAX = 7e4;
const int KMAX = 7e4;
const int LGMAX = 18;
 
int n,k;
vector<int> graph[NMAX + 5];
query_t paths[KMAX + 5];
 
int liniarizare[2 * NMAX + 5],sz_lin;
int lg2[2 * NMAX + 5];
int fst_pos[NMAX + 5];
int lvl[NMAX + 5];
int RMQ[LGMAX + 1][2 * NMAX + 5];
int order[NMAX + 5];
 
bool used_edge[NMAX + 5];
int low_bound[NMAX + 5];
int up_bound[NMAX + 5];
 
void prelca(int nod,int tata){
    liniarizare[++sz_lin] = nod;
    fst_pos[nod] = sz_lin;
    lvl[nod] = 1 + lvl[tata];
     
    for(auto it:graph[nod]){
        if(it != tata){
            prelca(it,nod);
            liniarizare[++sz_lin] = nod;
        }
    }
}
 
void make_lca(){
    prelca(1,0);
     
    lg2[0] = -1;
     
    for(int i = 1;i <= sz_lin;i++){
        lg2[i] = 1 + lg2[i / 2];
        RMQ[0][i] = liniarizare[i];
    }
     
    for(int i = 1;i <= LGMAX;i++){
        for(int j = 1;j <= sz_lin;j++){
            RMQ[i][j] = RMQ[i - 1][j];
             
            if(j >= (1 << (i - 1))){
                RMQ[i][j] = (lvl[RMQ[i - 1][j]] < lvl[RMQ[i - 1][j - (1 << (i - 1))]] ? RMQ[i - 1][j] : RMQ[i - 1][j - (1 << (i - 1))]);
            }
             
            else{
                RMQ[i][j] = 0;
            }
        }
    }
}
 
int lca(int u,int v){
    u = fst_pos[u];
    v = fst_pos[v];
     
    if(u > v){
        swap(u,v);
    }
     
    return lvl[RMQ[lg2[v - u + 1]][v]] < lvl[RMQ[lg2[v - u + 1]][u + (1 << lg2[v - u + 1]) - 1]] ? 
           RMQ[lg2[v - u + 1]][v] : RMQ[lg2[v - u + 1]][u + (1 << lg2[v - u + 1]) - 1];
}
 
int skip_list[NMAX + 5];
void init_skip_lists(int nod,int tata){
    skip_list[nod] = tata;
    for(auto it:graph[nod]){
        if(it != tata){
            init_skip_lists(it,nod);
        }
    }
}
 
void afis(int nod,int tata){
    if(tata){
        fprintf(g,"%d %d %d\n",nod,tata,low_bound[nod]);
    }
     
    for(auto it:graph[nod]){
        if(it != tata){
            afis(it,nod);
        }
    }
}
 
int main(){
 
    fscanf(f,"%d\n",&n);
     
    for(int i = 1;i < n;i++){
        int x,y;
        fscanf(f,"%d %d\n",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
     
    make_lca();
     
    fscanf(f,"%d\n",&k);
     
    for(int i = 1;i <= k;i++){
        paths[i].read();
        order[i] = i;
    }
     
    BipartiteMatcher matcher(k,n);
     
    for(int i = 1;i <= n;i++){
        low_bound[i] = 1;
        up_bound[i] = 1e9;
    }
     
    init_skip_lists(1,0);
    memset(used_edge,0,sizeof(used_edge));
     
    sort(order + 1,order + 1 + k,[](int &a,int &b){return paths[a].val < paths[b].val;});
     
    for(int i = 1;i <= k;i++){
        if(paths[order[i]].type == 0){
            int u = paths[order[i]].u;
            int v = paths[order[i]].v;
            int val = paths[order[i]].val;
            int w = lca(u,v);
     
     
            while(lvl[u] > lvl[w]){
                if(!used_edge[u]){
                    used_edge[u] = 1;
                    matcher.add_edge(order[i],u);
                    for(auto it:graph[u]){
                        if(lvl[it] > lvl[u]){
                            skip_list[it] = skip_list[u];
                        }
                    }
                    up_bound[u] = val;
                }
				int t = skip_list[u];
				skip_list[u] = w;
                u = t;
				
            }
             
            while(lvl[v] > lvl[w]){
                if(!used_edge[v]){
                    used_edge[v] = 1;
                    matcher.add_edge(order[i],v);
                    for(auto it:graph[v]){
                        if(lvl[it] > lvl[v]){
                            skip_list[it] = skip_list[v];
                        }
                    }
                    up_bound[v] = val;
                }
				int t = skip_list[v];
				skip_list[v] = w;
                v = t;
            }           
        }
    }
     
    init_skip_lists(1,0);
    memset(used_edge,0,sizeof(used_edge));
     
    sort(order + 1,order + 1 + k,[](int &a,int &b){return paths[a].val > paths[b].val;});
     
    for(int i = 1;i <= k;i++){
        if(paths[order[i]].type == 1){
            int u = paths[order[i]].u;
            int v = paths[order[i]].v;
            int val = paths[order[i]].val;
            int w = lca(u,v);
             
            while(lvl[u] > lvl[w]){
                if(!used_edge[u]){
                    used_edge[u] = 1;
                    matcher.add_edge(order[i],u);
                    for(auto it:graph[u]){
                        if(lvl[it] > lvl[u]){
                            skip_list[it] = skip_list[u];
                        }
                    }
                    low_bound[u] = val;
                }
				int t = skip_list[u];
				skip_list[u] = w;
                u = t;
            }
             
            while(lvl[v] > lvl[w]){
                if(!used_edge[v]){
                    used_edge[v] = 1;
                    matcher.add_edge(order[i],v);
                    for(auto it:graph[v]){
                        if(lvl[it] > lvl[v]){
                            skip_list[it] = skip_list[v];
                        }
                    }
                    low_bound[v] = val;
                }
				int t = skip_list[v];
				skip_list[v] = w;
                v = t;
            }
             
        }
    }
     
    matcher.max_match();
     
    for(int i = 1;i <= k;i++){
        if(matcher.L[i]){
            low_bound[matcher.L[i]] = up_bound[matcher.L[i]] = paths[i].val;
        }
    }
     
    afis(1,0);
     
     
    fclose(f);
    fclose(g);
 
    return 0;
}