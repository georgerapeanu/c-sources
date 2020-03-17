#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("viteza.in","r");
FILE *g = fopen("viteza.out","w");

const int LGMAX = 17;
const int NMAX = 1e5;
const int MMAX = 1e5;

struct query_t{
    int x,y,k;
    int id;

    bool operator < (const query_t &other)const{
        if(k != other.k){
            return k < other.k;
        }
        if(y != other.y){
            return y > other.y;
        }
        if(x != other.x){
            return x < other.x;
        }
        return id < other.id;
    }

    bool is_query(){
        return y != 1e9;
    }
};

int n,m;

vector<query_t> stuff;
vector<int> graph[NMAX + 1];

int l[NMAX + 1];
int r[NMAX + 1];
int lst_id;

int father[LGMAX + 1][NMAX + 1];
int lvl[NMAX + 1];

void dfs(int nod,int tata){
    lvl[nod] = 1 + lvl[tata];
    father[0][nod] = tata;
    l[nod] = ++lst_id;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
    }
    r[nod] = lst_id;
}

int aib[NMAX + 5];
int ans[NMAX + 5];
int a[NMAX + 5];

void update(int pos,int val){
    for(;pos <= n;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){
    int ans = 0;

    for(;pos;pos -= (-pos) & pos){
        ans += aib[pos];
    }
    return ans;
}

int lca(int u,int v){
    if(lvl[v] < lvl[u]){
        swap(u,v);
    }
    for(int h = LGMAX;h >= 0;h--){
        if(((lvl[v] - lvl[u]) >> h) & 1){
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

    return father[0][u];
}

const int LEN = 1 << 17;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans;
}

int main(){

    n = i32();
    m = i32();

    for(int i = 1;i < n;i++){
        int x,y;
        x = i32();
        y = i32();
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= n;i++){
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    for(int i = 1;i <= n;i++){
        a[i] = i32();
        stuff.push_back({i,int(1e9),a[i],0});
    }

    for(int i = 1;i <= m;i++){
        int x,y,k;
        x = i32();
        y = i32();
        k = i32();
        stuff.push_back({x,y,k,i});
    }

    sort(stuff.begin(),stuff.end());

    for(auto it:stuff){
        if(it.is_query()){
            int u = it.x;
            int v = it.y;
            int w = lca(it.x,it.y);
            ans[it.id] = query(l[u]) + query(l[v]) - 2 * query(l[w]) + (a[w] <= it.k);
        }
        else{
            update(l[it.x],1);
            update(r[it.x] + 1,-1);
        }
    }

    for(int i = 1;i <= m;i++){
        fprintf(g,"%d\n",ans[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
