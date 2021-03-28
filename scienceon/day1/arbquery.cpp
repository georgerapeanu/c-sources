#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("arbquery.in","r");
FILE *g = fopen("arbquery.out","w");

const int NMAX = 100000;
const int MOD = 1e9 + 7;

int n,q;
vector<pair<int,int> > graph[NMAX + 5];

int weight[NMAX + 5];
int sum[NMAX + 5];
const int LGMAX = 16;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b){
    a -= b;

    if(a < 0){
        a += MOD;
    }

    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }

    return p;
}

int father[LGMAX + 1][NMAX + 5];
int lvl[NMAX + 5];
int value[NMAX + 5];
int total_sum[NMAX + 5];

void predfs(int nod,int tata){
    father[0][nod] = tata;
    lvl[nod] = 1 + lvl[tata];
    weight[nod] = 1;

    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        predfs(it.first,nod);
        weight[nod] += weight[it.first];
        sum[nod] = add(sum[nod],add(sum[it.first], mult(it.second,weight[it.first])));
    }
}

void dfs(int nod,int tata){
    total_sum[nod] = add(value[nod],total_sum[tata]);
    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        weight[nod] -= weight[it.first];
        sum[nod] = scad(sum[nod],add(sum[it.first], mult(it.second,weight[it.first])));

        value[it.first] = add(mult(mult(weight[nod],weight[it.first]),it.second),add(mult(sum[nod],weight[it.first]),mult(sum[it.first],weight[nod])));
        
        sum[it.first] = add(sum[it.first],add(sum[nod],mult(it.second,weight[nod])));
        weight[it.first] += weight[nod];

        dfs(it.first,nod);

        sum[it.first] = scad(sum[it.first],add(sum[nod],mult(it.second,weight[nod])));
        weight[it.first] -= weight[nod];

        sum[nod] = add(sum[nod],add(sum[it.first], mult(it.second,weight[it.first])));
        weight[nod] += weight[it.first];
    }
}

int lca(int x,int y){
    if(lvl[x] > lvl[y]){
        swap(x,y);
    }

    for(int h = LGMAX;h >= 0;h--){
        if((lvl[y] - lvl[x]) >> h){
            y = father[h][y];
        }
    }

    if(x == y){
        return x;
    }
    
    for(int h = LGMAX;h >= 0;h--){
        if(father[h][x] != father[h][y]){
            x = father[h][x];
            y = father[h][y];
        }
    }

    return father[0][x];
}

int main(){

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1;i < n;i++){
        int u,v,w;
        fscanf(f,"%d %d %d",&u,&v,&w);
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }

    predfs(1,0);
    dfs(1,0);

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= n;i++){
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    while(q--){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        fprintf(g,"%d\n",scad(add(total_sum[x],total_sum[y]),mult(2 , total_sum[lca(x,y)])));
    }

    fclose(f);
    fclose(g);

    return 0;
}
