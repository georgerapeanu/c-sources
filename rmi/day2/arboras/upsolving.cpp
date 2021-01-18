#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const bool DEB = false;
const bool HOME = false;

const int MOD = 1e9 + 7;

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

class SegmentTree{
    struct node_t{
        pair<long long,long long> values;
        long long lazy;
        int sum = 0;
        bool is_leaf;

        node_t(){
            values = {0,0};
            lazy = 0;
            sum = 0;
            is_leaf = false;
        }

        node_t operator + (const node_t &other)const{
            node_t ans;
            ans.values = {0,0};///not applicable in non-leafs
            ans.sum = add(this->sum,other.sum);
            ans.is_leaf = false;
            ans.lazy = 0;
            return ans;
        }

        void propag(long long value,int len){
            if(is_leaf == true){
                values.first += value;
            }
            sum = add(sum,1LL * len * (value % MOD) % MOD);
            lazy += value;
        }

        void make_equal(){
            sum = add(sum,(values.first - values.second) % MOD);
            values.second = values.first;
        }

        void set_second(long long val){
            sum = add(sum,(val - values.second) % MOD);
            values.second = val;
        }
    };

    int n;
    vector<node_t> aint;

    void propag(int nod,int st,int dr){
        if(aint[nod].lazy == 0 || st == dr){
            return ;
        }

        int mid = (st + dr) / 2;

        aint[nod * 2].propag(aint[nod].lazy,mid - st + 1);
        aint[nod * 2 + 1].propag(aint[nod].lazy,dr - mid);
        aint[nod].lazy = 0;
    }

    void build(int nod,int st,int dr){
        aint[nod] = node_t();
        if(st == dr){
            aint[nod].is_leaf = true;
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid);
        build(nod * 2 + 1,mid + 1,dr);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    node_t access(int nod,int st,int dr,int pos){
        propag(nod,st,dr);
        if(st == dr){
            return aint[nod];
        }
        int mid = (st + dr) / 2;
        if(pos <= mid){
            return access(nod * 2,st,mid,pos);
        }else{
            return access(nod * 2 + 1,mid + 1,dr,pos);
        }
    }

    void make_equal(int nod,int st,int dr,int pos){
        propag(nod,st,dr);
        if(dr < pos || st > pos){
            return ;
        }
        if(st == dr){
            aint[nod].make_equal();
            return ;
        }
        int mid = (st + dr) / 2;

        make_equal(nod * 2,st,mid,pos);
        make_equal(nod * 2 + 1,mid + 1,dr,pos);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update(int nod,int st,int dr,int l,int r,long long add){
        propag(nod,st,dr);

        if(dr < l || st > r){
            return ;
        }

        if(l <= st && dr <= r){
            aint[nod].propag(add,dr - st + 1);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,l,r,add);
        update(nod * 2 + 1,mid + 1,dr,l,r,add);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update_second(int nod,int st,int dr,int pos,long long value){
        propag(nod,st,dr);
        if(dr < pos || st > pos){
            return ;
        }
        if(st == dr){
            aint[nod].set_second(value);
            return ;
        }

        int mid = (st + dr) / 2;

        update_second(nod * 2,st,mid,pos,value);
        update_second(nod * 2 + 1,mid + 1,dr,pos,value);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

public:

    SegmentTree(){
        this->n = 0;
    }

    SegmentTree(int n){
        this->n = n;
        this->aint = vector<node_t>(4 * n + 5);
        build(1,1,n);
    }

    pair<long long,long long> access(int pos){
        node_t tmp = access(1,1,n,pos);
        return tmp.values;
    }

    void make_equal(int pos){
        make_equal(1,1,n,pos);
    }

    void update(int l,int r,long long add){
        update(1,1,n,l,r,add);
    }

    void update_second(int pos,long long value){
        update_second(1,1,n,pos,value);
    }

    int query(){
        return aint[1].sum;
    }
};

const int NMAX = 1e5;

int n,q;
vector<SegmentTree> paths;
int root_path[NMAX + 5];
int id_path[NMAX + 5];
int pos_path[NMAX + 5];
int father[NMAX + 5];
int lvl[NMAX + 5];
int weight[NMAX + 5];
int last_path_id;
int heavy_sum = 0;

vector<int> graph[NMAX + 5];

void dfs_heavy(int nod,int tata){
    lvl[nod] = 1 + lvl[tata];
    father[nod] = tata;
    weight[nod] = 1;


    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs_heavy(it,nod);
        weight[nod] += weight[it];
    }
}

void dfs2_heavy(int nod,int tata,int whichPath){
    if(whichPath == -1){
        whichPath = ++last_path_id;
        pos_path[nod] = 1;
        id_path[nod] = last_path_id;
        root_path[last_path_id] = nod;
        paths.push_back(SegmentTree());
    }else{
        pos_path[nod] = 1 + pos_path[tata];
        id_path[nod] = id_path[tata];
    }

    int bigChild = -1;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        if(bigChild == -1 || weight[it] > weight[bigChild]){
            bigChild = it;
        }
    }

    if(bigChild == -1){
        paths[id_path[nod]] = SegmentTree(pos_path[nod]); 
    }else{
        dfs2_heavy(bigChild,nod,id_path[nod]);
        for(auto it:graph[nod]){
            if(it == tata || it == bigChild){
                continue;
            }
            dfs2_heavy(it,nod,-1);
        }
    }
}

void init_heavy(){
    last_path_id = -1;
    dfs_heavy(1,0);
    dfs2_heavy(1,0,-1);
    heavy_sum = 0;
}

int query_heavy(){
    return heavy_sum;
}

pair<long long,long long> access_heavy(int nod){
    return paths[id_path[nod]].access(pos_path[nod]);
}

void make_equal_heavy(int nod){
    if(DEB)fprintf(stderr,"make equal on %d\n",nod);
    heavy_sum = scad(heavy_sum,paths[id_path[nod]].query());
    paths[id_path[nod]].make_equal(pos_path[nod]);
    heavy_sum = add(heavy_sum,paths[id_path[nod]].query());
}

///x is an ancestor of y
void update_heavy(int x,int y,long long value){
    if(DEB)fprintf(stderr,"update first from %d to %d with %lld\n",x,y,value);
    while(true){
        if(id_path[x] == id_path[y]){
            heavy_sum = scad(heavy_sum,paths[id_path[y]].query());
            paths[id_path[y]].update(pos_path[x],pos_path[y],value);
            heavy_sum = add(heavy_sum,paths[id_path[y]].query());
            break;
        }else{
            heavy_sum = scad(heavy_sum,paths[id_path[y]].query());
            paths[id_path[y]].update(1,pos_path[y],value);
            heavy_sum = add(heavy_sum,paths[id_path[y]].query());
        }
        y = father[root_path[id_path[y]]];
    }
}

void update_second_heavy(int x,long long value){
    if(DEB)fprintf(stderr,"update second on %d with %lld\n",x,value);
    heavy_sum = scad(heavy_sum,paths[id_path[x]].query());
    paths[id_path[x]].update_second(pos_path[x],value);
    heavy_sum = add(heavy_sum,paths[id_path[x]].query());
}

long long initial_cost[NMAX + 5];
long long init_best[NMAX + 5];
long long init_sbest[NMAX + 5];

void init_dfs(int nod,int tata){
    init_best[nod] = 0;
    init_sbest[nod] = 0;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        init_dfs(it,nod);
        long long cost = init_best[it] + initial_cost[it];

        if(init_best[nod] < cost){
            init_sbest[nod] = init_best[nod];
            init_best[nod] = cost;
        }else if(init_sbest[nod] < cost){
            init_sbest[nod] = cost;
        }
    }

    update_heavy(nod,nod,init_sbest[nod]);
    make_equal_heavy(nod);
    update_heavy(nod,nod,init_best[nod] - init_sbest[nod]);
}

int l[NMAX + 5];
int r[NMAX + 5];
int mark_aint[4 * NMAX + 5];
int lin[NMAX + 5];
int mark_lst;

void dfs_mark(int nod,int tata){
    l[nod] = ++mark_lst;
    lin[l[nod]] = nod;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs_mark(it,nod);
    }

    r[nod] = mark_lst;
}

void init_mark(){
    mark_lst = 0;
    dfs_mark(1,0);
}

void update_mark(int nod,int st,int dr,int pos,int val){
    if(dr < pos || st > pos){
        return ;
    }
    if(st == dr){
        mark_aint[nod] = val;
        return ;
    }
    int mid = (st + dr) / 2;
    update_mark(nod * 2,st,mid,pos,val);
    update_mark(nod * 2 + 1,mid + 1,dr,pos,val);
    mark_aint[nod] = max(mark_aint[nod * 2],mark_aint[nod * 2 + 1]);
}

int query_mark(int nod,int st,int dr,int l,int r,int val){
    if(r < st || l > dr){
        return -1;
    }
    int mid = (st + dr) / 2;
    if(l <= st && dr <= r){
        if(mark_aint[nod] < val){
            return -1;
        }else if(st == dr){
            return st;
        }
        else if(mark_aint[nod * 2 + 1] >= val){
            return query_mark(nod * 2 + 1,mid + 1,dr,l,r,val);
        }else{
            return query_mark(nod * 2,st,mid,l,r,val);
        }
    }


    int a = query_mark(nod * 2,st,mid,l,r,val);
    int b = query_mark(nod * 2 + 1,mid + 1,dr,l,r,val);

    if(a == -1){
        return b;
    }
    if(b == -1){
        return a;
    }

    return b;
}

int prefered_child[NMAX + 5];

int get_first_marked(int nod){
    int tmp = lin[query_mark(1,1,n,1,l[nod],l[nod])];
    if(DEB)fprintf(stderr,"get marked %d is %d\n",nod,tmp);
    return tmp;
}

void set_mark(int nod){
    if(DEB)fprintf(stderr,"set %d on %d with %d\n",nod,l[nod],r[nod]);
    update_mark(1,1,n,l[nod],r[nod]);
}

void unset_mark(int nod){
    if(DEB)fprintf(stderr,"unset %d\n",nod);
    update_mark(1,1,n,l[nod],0);
}

void init(){
    init_dfs(1,0);
    for(int i = 2;i <= n;i++){
        if(init_best[father[i]] == init_best[i] + initial_cost[i]){
            prefered_child[father[i]] = i;
        }
    }
    for(int i = 1;i <= n;i++){
        if(prefered_child[father[i]] != i){
            set_mark(i);
        }
    }
}

void update(int nod,int add){
    
    if(nod == 1){
        return ;
    }

    pair<long long,long long> a = access_heavy(father[nod]);
    pair<long long,long long> b = access_heavy(nod);

    initial_cost[nod] += add;

    if(b.first + initial_cost[nod] > a.first){
        add = b.first + initial_cost[nod] - a.first;
        if(prefered_child[father[nod]] != nod){
            make_equal_heavy(father[nod]);
            set_mark(prefered_child[father[nod]]);
            unset_mark(nod);
            prefered_child[father[nod]] = nod;
        }
        nod = father[nod];
    }else if(b.first + initial_cost[nod] > a.second){
        update_second_heavy(father[nod],b.first + initial_cost[nod]);
        return ;
    }else{
        return ;
    }


    while(nod != 0){
        int y = get_first_marked(nod);

        update_heavy(y,nod,add);

        if(father[y] == 0){
            break;
        }

        a = access_heavy(father[y]);
        b = access_heavy(y);
       
        if(b.first + initial_cost[y] > a.first){
            add = b.first + initial_cost[y] - a.first;
            set_mark(prefered_child[father[y]]);
            unset_mark(y);
            prefered_child[father[y]] = y;
            make_equal_heavy(father[y]);
        }else if(b.first + initial_cost[y] > a.second){
            update_second_heavy(father[y],b.first + initial_cost[y]);
            break;
        }
        else{
            break;
        }

        nod = father[y];
    }

}

int query(){
    return query_heavy();
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans;
}

int main(){

    if(HOME == false){
        freopen("arboras.in","r",stdin);
        freopen("arboras.out","w",stdout);
    }

    n = i32();

    for(int i = 2;i <= n;i++){
        father[i] = i32();
        father[i]++;
        graph[father[i]].push_back(i);
        graph[i].push_back(father[i]);
    }

    for(int i = 2;i <= n;i++){
        initial_cost[i] = i32();
    }


    init_mark();
    init_heavy();
    
    if(DEB){
        for(int i = 1;i <= n;i++){
            fprintf(stderr,"%d %d %d %d\n",i,father[i],id_path[i],pos_path[i]);
        }
    }
    init();

    if(DEB)fprintf(stderr,"DONE INIT\n\n\n\n");

    printf("%d\n",query());

    q = i32();

    while(q--){
        int nod,add;
        nod = i32();
        add = i32();
        nod++;
        update(nod,add);
        printf("%d\n",query());
    }

    return 0;
}

