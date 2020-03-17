#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e6;

struct point_t{
    int x,y,z;

    bool operator < (const point_t &other)const{
        if(x != other.x){
            return x < other.x;
        }
        if(y != other.y){
            return y < other.y;
        }
        return z < other.z;
    }

    bool is_query(){
        return (y == 0);
    }
};

struct node_t{
    long long val;
    long long lazy;

    node_t(){
        val = 0;
        lazy = 0;
    }

    node_t(long long val,long long lazy){
        this->val = val;
        this->lazy = lazy;
    }

    node_t operator + (const node_t &other)const{
        return node_t(max(val,other.val),0);
    }
};

int n,m,p;
vector<point_t> stuff;
long long bst_cost[NMAX + 5];

node_t aint[4 * NMAX + 5];

void propag(int nod,int st,int dr){
    if(st == dr || aint[nod].lazy == 0){
        return ;
    }

    aint[nod * 2].val += aint[nod].lazy;
    aint[nod * 2].lazy += aint[nod].lazy;
    aint[nod * 2 + 1].val += aint[nod].lazy;
    aint[nod * 2 + 1].lazy += aint[nod].lazy;

    aint[nod].lazy = 0;
}

void build(int nod,int st,int dr){
    if(st == dr){
        aint[nod] = node_t(bst_cost[st],0);
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int l,int r,int val){
    propag(nod,st,dr);
    if(r < st || l > dr){
        return ;
    }
    if(l <= st && dr <= r){
        aint[nod].lazy += val;
        aint[nod].val += val;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,val);
    update(nod * 2 + 1,mid + 1,dr,l,r,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

long long query(){
    return aint[1].val;
}

int main(){

    for(int i = 1;i <= NMAX;i++){
        bst_cost[i] = -1e18;
    }

    scanf("%d %d %d",&n,&m,&p);

    for(int i = 1;i <= n;i++){
        int a,ca;
        scanf("%d %d",&a,&ca);
        stuff.push_back({a,0,-ca});
    }

    for(int i = 1;i <= m;i++){
        int b,cb;
        scanf("%d %d",&b,&cb);
        bst_cost[b] = max(bst_cost[b],-(long long)cb);
    }

    for(int i = 1;i <= p;i++){
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        stuff.push_back({x,y,z});
    }

    build(1,1,NMAX);

    sort(stuff.begin(),stuff.end());

    long long ans = -1e18;

    for(auto it:stuff){
        if(it.is_query()){
            ans = max(ans,query() + it.z);
        }
        else{
            update(1,1,NMAX,it.y + 1,NMAX,it.z);
        }
    }

    printf("%lld\n",ans);

    return 0;
}
