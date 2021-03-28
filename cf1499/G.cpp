#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int MMAX = 2e5;
const int QMAX = 2e5;

struct edge_t{
    int x,y;
    int id;
};

int n1,n2,m,q;

int component[2 * NMAX + 5];
int color[MMAX + QMAX + 5];
int last_color[2 * NMAX + 5];
int cnt[MMAX + QMAX + 5];
vector<edge_t> component_edges[MMAX + QMAX + 5];

const int MOD = 998244353;
int pw2[MMAX + QMAX + 5];
int _hash = 0;
int cnt_red;

void set_color(int id,int _color){
    _hash -= pw2[id] * color[id];
    cnt_red -= color[id];
    if(_hash < 0){
        _hash += MOD;
    }
    color[id] = _color;
    _hash += pw2[id] * color[id];
    cnt_red += color[id];
    if(_hash >= MOD){
        _hash -= MOD;
    }
}

void unite(const edge_t &edge){
    int x = edge.x;
    int y = edge.y;

    if(component[x] == 0 && component[y] == 0){
        component[x] = component[y] = edge.id;
        last_color[x] = last_color[y] = 0;
        set_color(edge.id,0);
        component_edges[edge.id].push_back(edge);
        return ;
    }

    if(component[x] == 0){
        swap(x,y);
    }
    
    if(component[y] == 0){
        component[y] = component[x];
        component[x] = 0;
        last_color[y] = last_color[x] ^ 1;
        set_color(edge.id,last_color[y]);
        component_edges[component[y]].push_back(edge);
        return ;
    }

    if(component[x] == component[y]){
        set_color(edge.id,last_color[x] ^ 1);
        last_color[x] = last_color[y] = 0;
        component[x] = component[y] = 0;
        return ;
    }

    if(component_edges[component[x]].size() > component_edges[component[y]].size()){
        swap(x,y);
    }

    int tmp = component[x];
    bool sw = (last_color[x] != last_color[y]);
    for(auto it:component_edges[tmp]){
        component_edges[component[y]].push_back(it);
        if(sw){
            set_color(it.id,color[it.id] ^ 1);
            if(component[it.x] != 0){
                last_color[it.x] ^= 1;
            }
            if(component[it.y] != 0){
                last_color[it.y] ^= 1;
            }
        }
        if(component[it.x] != 0){
            component[it.x] = component[y];
        }
        if(component[it.y] != 0){
            component[it.y] = component[y];
        }
    }
    set_color(edge.id,last_color[edge.x] ^ 1);
    component[x] = component[y] = 0;
}

int main(){

    pw2[0] = 1;

    for(int i = 1;i <= MMAX + QMAX;i++){
        pw2[i] = (pw2[i - 1] << 1);
        if(pw2[i] >= MOD){
            pw2[i] -= MOD;
        }
    }

    scanf("%d %d %d",&n1,&n2,&m);

    for(int i = 1;i <= m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        y += n1;
        unite({x,y,i});
    }

    scanf("%d",&q);

    while(q--){
        int t;
        int x,y;
        scanf("%d",&t);
        if(t == 1){
            m++;
            scanf("%d %d",&x,&y);
            y += n1;
            unite({x,y,m});
            printf("%d\n",_hash);
            fflush(stdout);
        }else{
            printf("%d ",cnt_red);
            for(int i = 1;i <= m;i++){
                if(color[i] == 1){
                    printf("%d ",i);
                }
            }
            printf("\n");
            fflush(stdout);
        }

    }
    

    return 0;
}
