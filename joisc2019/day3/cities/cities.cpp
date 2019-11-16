#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2e5;

struct node_t {
    long long lazy;
    long long ma_val;
    int ma_pos;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.lazy = false;
        if(this->ma_val < other.ma_val) {
            ans.ma_val = other.ma_val;
            ans.ma_pos = other.ma_pos;
        }
        else {
            ans.ma_val = this->ma_val;
            ans.ma_pos = this->ma_pos;
        }
        return ans;
    }

} aint[4 * NMAX + 5];

void propag(int nod,int st,int dr) {
    if(st == dr || aint[nod].lazy == 0) {
        return ;
    }

    aint[nod * 2].lazy += aint[nod].lazy;
    aint[nod * 2].ma_val += aint[nod].lazy;

    aint[nod * 2 + 1].lazy += aint[nod].lazy;
    aint[nod * 2 + 1].ma_val += aint[nod].lazy;

    aint[nod].lazy = 0;
}

void build(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod].lazy = 0;
        aint[nod].ma_val = 0;
        aint[nod].ma_pos = st;
        return ;
    }
    int mid = (st + dr) / 2;
    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int l,int r,long long val) {
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return ;
    }
    if(l <= st && dr <= r) {
        aint[nod].lazy += val;
        aint[nod].ma_val += val;
        return ;
    }
    int mid = (st + dr) / 2;
    update(nod * 2,st,mid,l,r,val);
    update(nod * 2 + 1,mid + 1,dr,l,r,val);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

int n;
vector< pair<int,pair<int,int> > > graph[NMAX + 5];
long long subtree_cost[NMAX + 5];
long long singular_cost[NMAX + 5];

void predfs(int nod,int tata) {
    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        predfs(it.first,nod);
        subtree_cost[nod] += subtree_cost[it.first] + it.second.second;
    }
}

long long dfs_singular(int nod,int tata,long long cost) {
    long long ans = singular_cost[nod] = cost;
    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        ans = max(ans,dfs_singular(it.first,nod,cost - it.second.second + it.second.first));
    }
    return ans;
}

pair<long long,int> dfs_far(int nod,int tata,long long cost) {
    pair<long long,int> bst = {cost + singular_cost[nod],nod};

    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        bst = max(bst,dfs_far(it.first,nod,cost + it.second.first + it.second.second));
    }

    return bst;
}

int q;
long long ans[NMAX + 5];
int father[NMAX + 5];
int fst[NMAX + 5];
int lst[NMAX + 5];
int euler;
bool added[NMAX + 5];
int lin[NMAX + 5];
int father_edge[NMAX + 5];

void afis(int nod,int st,int dr) {
    propag(nod,st,dr);
    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    afis(nod * 2,st,mid);
    afis(nod * 2 + 1,mid + 1,dr);
}

void root_tree(int nod,int tata) {
    father[nod] = tata;
    lin[++euler] = nod;
    fst[nod] = euler;

    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        father_edge[it.first] = it.second.first;
        root_tree(it.first,nod);
    }

    lst[nod] = euler;
}

void do_costs(int nod,long long father_cost) {
    update(1,1,n,fst[nod],fst[nod],father_cost);
    for(auto it:graph[nod]) {
        if(it.first == father[nod]) {
            continue;
        }
        do_costs(it.first,father_cost + it.second.first);
    }
}

void add_node(int nod) {
    while(added[nod] == false) {
        update(1,1,n,fst[nod],lst[nod],-father_edge[nod]);
        added[nod] = true;
        nod = father[nod];
    }
}

node_t get_max() {
    propag(1,1,n);
    return aint[1];
}

int main() {

    scanf("%d",&n);

    build(1,1,n);
    long long total_sum = 0;

    for(int i = 1; i < n; i++) {
        int a,b,c,d;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        total_sum += c + d;
        graph[a].push_back({b,{c,d}});
        graph[b].push_back({a,{d,c}});
    }

    predfs(1,0);
    ans[1] = dfs_singular(1,0,subtree_cost[1]);
    if(n > 1) {
        pair<long long,int> tmp1 = dfs_far(1,0,0);
        pair<long long,int> tmp2 = dfs_far(tmp1.second,0,singular_cost[tmp1.second]);
        ans[2] = tmp2.first / 2;

        added[tmp1.second] = true;
        root_tree(tmp1.second,0);
        do_costs(tmp1.second,0);
        add_node(tmp2.second);

        afis(1,1,n);

        for(int i = 3; i <= n; i++) {
            node_t tmp = get_max();
            ans[i] = ans[i - 1] + tmp.ma_val;
            add_node(lin[tmp.ma_pos]);
        }
    }

    scanf("%d",&q);

    while(q--) {
        int a;
        scanf("%d",&a);
        printf("%lld\n",total_sum - ans[a]);
    }

    return 0;
}
