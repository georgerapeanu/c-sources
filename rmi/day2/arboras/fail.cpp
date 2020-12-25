#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 1e5;
const int LGMAX = 16;

class FenwickTree{
    int n;
    vector<long long> aib;
    
public:

    FenwickTree(int n){
        this->n = n;
        aib = vector<long long>(n + 1,0);
    }

    void update(int pos,int val){
        for(;pos <= n;pos += (-pos) & pos){
            aib[pos] += val;
        }
    }

    long long query(int pos){
        long long ans = 0;

        for(;pos;pos -= (-pos) & pos){
            ans += aib[pos];
        }

        return ans;
    }
}aib(0);

int n,q;

vector<int> graph[NMAX + 5];

int lst = 0;
int st[NMAX + 5];
int dr[NMAX + 5];
int father[LGMAX + 1][NMAX + 1];
int weight[NMAX + 5];
vector<SegmentTree> trees;
vector<vector<int> > chains;
int which_tree[NMAX + 5];
int where[NMAX + 5];

void dfs(int nod){
    st[nod] = ++lst;
    weight[nod] = 1;

    for(auto it:graph[nod]){
        dfs(it);
        weight[nod] += it;
    }

    dr[nod] = ++lst;
}

void dfs2(int nod,int wh = -1,int lvl = -1){
    if(wh == -1){
        chains.push_back(vector<int>());
        wh = (int)chains.size() - 1;
        lvl = 1;
    }
    which_tree[nod] = wh;
    where[nod] = lvl;
    chains[wh].push_back(nod);

    int best_child = -1;

    for(auto it:graph[nod]){
        if(best_child == -1 || weight[best_child] < weight[it]){
            best_child = it;
        }
    }

    if(best_child != -1){
        dfs2(it,wh,lvl + 1);
    }

    for(auto it:graph[nod]){
        if(it != best_child){
            dfs2(it,-1,-1);
        }
    }
}

void update(int nod,int add){
    aib.update(st[nod],add);
    aib.update(dr[nod],-add);

    int r = 
}

int main(){

    scanf("%d %d",&n,&q);

    for(int i = 2;i <= n;i++){
        scanf("%d",&father[0][i]);
        father[0][i]++;
        graph[father[0][i]].push_back(i);
    }

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= n;i++){
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    dfs(1);
    dfs2(1);
    for(int i = 0;i < (int)chains.size();i++){
        trees.push_back(SegmentTree(chains.size()));
    }
    aib = FenwickTree(n);
    
    for(int i = 2;i <= n;i++){
        int dist;
        scanf("%d",&dist);
        update(i,dist);
    }

    printf("%lld\n",query());

    while(q--){
        int a,b;
        scanf("%d %d",&a,&b);
        update(a,b);
        printf("%lld\n",query());
    }


    return 0;
}
