#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int LGMAX = 18;

int n;
vector<int> graph[NMAX + 5];
int weight[NMAX + 5];

int father[LGMAX + 1][NMAX + 1];
int lvl[NMAX + 1];

void predfs(int nod,int tata){
    weight[nod] = 1;
    father[0][nod] = tata;
    lvl[nod] = 1 + lvl[tata];
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        predfs(it,nod);
        weight[nod] += weight[it];
    }
}

int get_centroid(int nod){
    int tata = 0;

    while(true){
        int bigChild = -1;
        for(auto it:graph[nod]){
            if(it == tata){
                continue;
            }
            if(bigChild == -1 || weight[it] > weight[bigChild]){
                bigChild = it;
            }
        }
        if(bigChild == -1 || weight[bigChild] * 2 <= n){
            break;
        }
        tata = nod;
        nod = bigChild;
    }

    return nod;
}

vector<int> events[NMAX + 5];
map<int,int> stuff;

vector<int> nodes[NMAX + 5];

int lca(int u,int v){
    if(lvl[u] > lvl[v]){
        swap(u,v);
    }

    for(int h = LGMAX;h >= 0;h--){
        if((lvl[v] - lvl[u]) >> h){
            v = father[h][v];
        }
    }

    if(u == v){
        return u;
    }

    for(int h = LGMAX;h >= 0;h--){
        if(father[h][u] != father[h][v]){
            u = father[h][u];
            v = father[h][v];
        }
    }

    return father[0][v];
}

int dist(int u,int v){
    return lvl[u] + lvl[v] - 2 * lvl[lca(u,v)] + 1;
}

int ans[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i < n;i++){
        int x,y;
        scanf("%d %d",&x,&y);

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    predfs(1,0);
    int root = get_centroid(1);
    predfs(root,0);

    for(int i = 1;i <= n;i++){
        if(root != i){
            nodes[weight[i]].push_back(i);
        }
    }

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= n;i++){
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    int u = root,v = root;
    int d = 1;

    for(int i = n / 2;i >= 1;i--){
        for(auto it:nodes[i]){
            int c = dist(it,u);
            int e = dist(it,v);
            if(c > d){
                d = c;
                v = it;
            }
            else if(e > d){
                d = e;
                u = it;
            }
        }
        ans[i] = d;
    }

    for(int i = 1;i <= n;i++){
        if(i & 1){
            printf("1\n");
        }else{
            printf("%d\n",ans[i / 2]);
        }
    }

    return 0;
}
