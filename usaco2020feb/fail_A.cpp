#include <cstdio>

using namespace std;

const int NMAX = 2e5;

struct event_t{
    int value;
    int pos;

    bool operator < (const event_t &other)const{
        return this->value < other.value;
    }
};

struct node_t{
    int father;
    int l;
    int r;

    node_t(){
        father = 0;
        l = 0;
        r = 0;
    }
};

class DSU{
    int n;
    vector<node_t> dsu;

public:

    DSU(int n){
        this->n = n;
        this->dsu = vector<node_t>(n + 5);
        for(int i = 1;i <= n;i++){
            dsu[i].l = dsu[i].r = i;
        }
    }

    int find_root(int nod){
        if(dsu[nod].father == 0){
            return nod;
        }
        return dsu[nod].father = find_root(dsu[nod].father);
    }

    bool unite(int x,int y){
        x = find_root(x);
        y = find_root(y);

        if(x == y){
            return false;
        }

        dsu[x].father = y;
        dsu[y].l = min(dsu[y].l,dsu[x].l);
        dsu[y].r = max(dsu[y].r,dsu[x].r);

        return true;
    }
   
    node_t access(int nod){
        return dsu[nod];
    }
};

int n,q;
int v[NMAX + 5];
vector<event_t> events;
bool active[NMAX + 5];

int main(){

    scanf("%d %d",&n,&q);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
        events.push_back({v[i],i});
    }

    sort(events.begin(),events.end());

    for(auto it:events){
        active[it] = true;
    }

    return 0;
}
