#include <bits/stdc++.h>

using namespace std;

struct edge_t{
    int c;
    int u;
    int v;
    int tp;

    bool operator < (const edge_t &other)const{
        if(c != other.c){
            return c < other.c;
        }
        if(u != other.u){
            return u < other.u;
        }
        if(v != other.v){
            return v < other.v;
        }
        return tp < other.tp;
    }

    int other(int nod){
        return nod ^ u ^ v;
    }
};

const int NMAX = 5e5;

int n,m,k;
int c[NMAX + 5];
vector<int> graph[NMAX + 5];
vector<edge_t> graph2[NMAX + 5];
vector<int> nodes[NMAX + 5];

int node_side[NMAX + 5];
int viz[NMAX + 5];
int lst_comp;
int comp[NMAX + 5];
int col[NMAX + 5];

int valid_suff[NMAX + 5];

void dfs(int nod,int tata,int &valid){
    comp[nod] = lst_comp;
    viz[nod] = true;
    node_side[nod] = node_side[tata] ^ 1;

    for(auto it:graph[nod]){
        if(it != tata && c[it] == c[nod]){
            if(viz[it] == 0){
                dfs(it,nod,valid);
            }
            else if(node_side[it] == node_side[nod]){
                valid = 0;
            }
        }
    }
}

bool dfs2(int nod,int tata){
    viz[nod] = true;
    for(auto it:graph2[nod]){
        if(it.other(nod) == tata){
            continue;
        }
        if(viz[it.other(nod)] == true){
            if((col[it.other(nod)] ^ it.tp ^ col[nod]) != 0){
                return 0;
            }
        }
        else{
            col[it.other(nod)] = col[nod] ^ it.tp;
            if(dfs2(it.other(nod),nod) == 0){
                return 0;
            }
        }
    }
    return 1;
}

int main(){

    scanf("%d %d %d",&n,&m,&k);

    for(int i = 1;i <= n;i++){
        scanf("%d",&c[i]);
    }

    for(int i = 1;i <= m;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int i = 1;i <= k;i++){
        valid_suff[i] = 1;
    }

    for(int i = 1;i <= n;i++){
        if(viz[i] == 0){
            lst_comp++;
            dfs(i,0,valid_suff[c[i]]);
        }
        nodes[c[i]].push_back(i);
    }

    for(int i = k - 1;i >= 1;i--){
        valid_suff[i] += valid_suff[i + 1];
    }

    long long ans = 0;

    for(int i = 1;i <= k;i++){

        if(valid_suff[i] == valid_suff[i + 1]){
            continue;
        }

        ans += valid_suff[i + 1];

        vector<edge_t> v;

        for(auto it:nodes[i]){
            for(auto it2:graph[it]){
                if(c[it2] <= c[it]){
                    continue;
                }
                v.push_back({c[it2],comp[it],comp[it2],node_side[it] ^ node_side[it2] ^ 1});
            }
        }

        sort(v.begin(),v.end());

        for(int i = 0;i < (int)v.size();){
            edge_t tmp = v[i];

            int t_i = i;


            while(i < (int)v.size() && tmp.c == v[i].c){
                graph2[v[i].u].push_back(v[i]);
                graph2[v[i].v].push_back(v[i]);
                viz[v[i].u] = 0;
                viz[v[i].v] = 0;
                col[v[i].u] = 0;
                col[v[i].v] = 0;
                i++;
            }


            if(valid_suff[tmp.c] != valid_suff[tmp.c + 1]){
                i = t_i;
                bool ok = true;
                while(i < (int)v.size() && tmp.c == v[i].c){
                    if(viz[v[i].u] == 0){
                        ok &= dfs2(v[i].u,0);
                    }
                    i++;
                }
    
                if(ok == false){
                    ans--;
                }
            }
    

            i = t_i;
            while(i < (int)v.size() && tmp.c == v[i].c){
                graph2[v[i].u].clear();
                graph2[v[i].v].clear();
                i++;
            }
        }

    }

    printf("%lld\n",ans);

    return 0;
}
