#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int LGMAX = 18;
int n,q;

vector<int> graph[NMAX + 5];

int root = 1;
int lvl[NMAX + 5];
int pos[NMAX + 5];
int rmq[LGMAX + 1][2 * NMAX + 5];
int lg2[2 * NMAX + 5];
int len;
const int DEB = false;

void predfs(int nod,int tata){
    lvl[nod] = 1 + lvl[tata];
    rmq[0][++len] = nod;
    pos[nod] = len;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        predfs(it,nod);
        rmq[0][++len] = nod;
    }
}


int get_best(int a,int b){
    if(a == 0)return b;
    if(b == 0)return a;
    return lvl[a] < lvl[b] ? a:b;
}

void make_lca(){

    lg2[0] = -1;

    for(int i = 1;i <= len;i++){
        lg2[i] = 1 + lg2[i >> 1];
    }

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= len;i++){
            rmq[h][i] = rmq[h - 1][i];
            if(i >= (1 << (h - 1))){
                rmq[h][i] = get_best(rmq[h - 1][i],rmq[h - 1][i - (1 << (h - 1))]);
            }
        }
    }
}

int lca(int a,int b){
    a = pos[a];
    b = pos[b];
    if(a > b){
        swap(a,b);
    }

    int h = lg2[b - a + 1];

    return get_best(rmq[h][b],rmq[h][a + (1 << h) - 1]);
}

int w[NMAX + 5];
int cnt_even[NMAX + 5];
vector<int> graph2[NMAX + 5];


void dfs(int nod,int tata){
    if(graph[nod].size() == (tata != 0)){
       w[nod] = 1; 
    }
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
        w[nod] ^= w[it];
    }
}

int total_cnt = 0;
int cnt_leafs = 0;

void dfs2(int nod,int tata){
    if(tata){
        cnt_even[nod] = (w[nod] == 0) + cnt_even[tata];
        total_cnt += (w[nod] == 0);
    }
    cnt_leafs += (graph[nod].size() == (tata != 0));
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs2(it,nod);
    }
}

bool cmp(int a,int b){
    return pos[a] < pos[b];
}

void add_edge(int u,int v){
    if(u == v)return ;
    graph2[u].push_back(v);
    graph2[v].push_back(u);
    if(DEB)printf("add edge %d %d\n",u,v);
}

int flip[NMAX + 5];

void dfs3(int nod,int tata,int &ans){
    if(DEB)printf("dfs3 %d %d\n",nod,tata);
    for(auto it:graph2[nod]){
        if(it == tata){
            continue;
        }
        dfs3(it,nod,ans);
        flip[nod] ^= flip[it];
    }
    if(flip[nod]){
        ans -= (cnt_even[nod] - cnt_even[tata]);
        ans += (lvl[nod] - lvl[tata]) - (cnt_even[nod] - cnt_even[tata]);
    }
}

void cleanup_dfs(int nod,int tata){
    for(auto it:graph2[nod]){
        if(it == tata){
            continue;
        }
        cleanup_dfs(it,nod);
    }
    flip[nod] = 0;
    graph2[nod].clear();
}

int main(){

    scanf("%d %d",&n,&q);

    for(int i = 1;i < n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }


    for(int i = 1;i <= n;i++){
        if((int)graph[i].size() > 1){
            root = i;
            break;
        }
    }

    predfs(root,0);

    make_lca();

    dfs(root,0);
    dfs2(root,0);
    if(DEB)printf("root is %d %d\n",root,total_cnt);

    for(int i = 1;i <= q;i++){
        if(DEB)printf("new batch\n");
        int len = 0;
        scanf("%d",&len);
        vector<int> nodes;
        int tmp_leafs = cnt_leafs;
        for(int t = 1;t <= len;t++){
            int nod;
            scanf("%d",&nod);
            nodes.push_back(nod);
        }

        for(auto it:nodes){
            flip[it] = (graph[it].size() == 1 ? 1:0);
            tmp_leafs++;
        }

        for(auto it:nodes){
            flip[it] ^= 1;
        }

        sort(nodes.begin(),nodes.end());
        nodes.resize(unique(nodes.begin(),nodes.end()) - nodes.begin());
        sort(nodes.begin(),nodes.end(),cmp);

        for(auto it:nodes){
            if(graph[it].size() == 1){
                tmp_leafs--;
            }
        }

        vector<int> tmp;

        for(auto it:nodes){
            while((int)tmp.size() > 1){
                int v = tmp[(int)tmp.size() - 1];
                int u = tmp[(int)tmp.size() - 2];

                if(lvl[lca(v,it)] <= lvl[lca(u,v)]){
                    add_edge(lca(u,v),u);
                    add_edge(lca(u,v),v);
                    tmp.pop_back();
                    tmp.back() = lca(u,v);
                }
                else{
                    break;
                }
            }
            tmp.push_back(it);
        }

        while((int)tmp.size() > 1){
            int v = tmp[(int)tmp.size() - 1];
            int u = tmp[(int)tmp.size() - 2];
            add_edge(lca(u,v),u);
            add_edge(lca(u,v),v);
            tmp.pop_back();
            tmp.back() = lca(u,v);
        }

        int ans = total_cnt + (n + len) - 1;

        if((tmp_leafs) % 2 == 1){
            ans = -1;
        }
        else{
            dfs3(tmp[0],root,ans);
        }

        cleanup_dfs(tmp[0],root);

        printf("%d\n",ans);
    }

    return 0;
}
