#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;
const int VMAX = 2e5;

class SegmentTree{
    struct node_t{
        int lazy;
        int id;
        int value;

        node_t(){
            lazy = 0;
            id = 1e9;
            value = 0;
        }

        node_t operator + (const node_t &other)const{
            node_t ans;
            ans.lazy = 0;

            if(this->value < other.value){
                ans.value = other.value;
                ans.id = other.id;
            }else if(this->value > other.value){
                ans.value = this->value;
                ans.id = this->id;
            }else{
                ans.value = this->value;
                ans.id = min(this->id,other.id);
            }
            return ans;
        }

        void propag(int lazy){
            this->value += lazy;
            this->lazy += lazy;
        }
    };

    int n;
    vector<node_t> aint;

    void propag(int nod,int st,int dr){
        if(aint[nod].lazy == 0 || st == dr){
            return ;
        }

        aint[nod * 2].propag(aint[nod].lazy);
        aint[nod * 2 + 1].propag(aint[nod].lazy);
        
        aint[nod].lazy = 0;
    }

    void build(int nod,int st,int dr){
        if(st == dr){
            aint[nod] = node_t();
            aint[nod].id = st;
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid);
        build(nod * 2 + 1,mid + 1,dr);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update(int nod,int st,int dr,int l,int r,int val){
        propag(nod,st,dr);

        if(dr < l || st > r){
            return ;
        }

        if(l <= st && dr <= r){
            aint[nod].propag(val);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,l,r,val);
        update(nod * 2 + 1,mid + 1,dr,l,r,val);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

public:

    SegmentTree(int n){
        this->n = n;
        this->aint = vector<node_t>(4 * n + 5);
        this->build(1,1,n);
    }

    void update(int l,int r,int val){
        this->update(1,1,n,l,r,val);
    }

    node_t query(){
        return aint[1];
    }
};

int n;
int v[NMAX + 5];
int q;

SegmentTree aint(VMAX);

void add(int pos,int sgn){
    if(pos < 1){
        return ;
    }
    if(pos < n){
        int l = min(v[pos],v[pos + 1]) + 1;
        int r = max(v[pos],v[pos + 1]) - 1;
        if(l <= r){
            aint.update(l,r,sgn);
        }
    }
}

int main(){

    scanf("%d ",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    for(int i = 1;i <= n;i++){
        add(i,1);
        aint.update(v[i],v[i],1);
    }

    scanf("%d",&q);

    while(q--){
        int pos,val;
        scanf("%d %d",&pos,&val);
        add(pos - 1,-1);
        add(pos,-1);
        aint.update(v[pos],v[pos],-1);
        v[pos] = val;
        add(pos - 1,1);
        add(pos,1);
        aint.update(v[pos],v[pos],1);
        printf("%d %d\n",aint.query().id,aint.query().value);
    }

    return 0;
}
