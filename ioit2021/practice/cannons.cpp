#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

class SegmentTree{
    struct lazy_t{
        int a,b;

        lazy_t(){
            a = 0;
            b = -inf;
        }

        lazy_t(int a,int b){
            this->a = a;
            this->b = b;
        }

        bool is_valid()const{
            return b > -inf;
        }

        int eval(int x)const{
            return a * x + b;
        }
    };
    struct node_t{
        int left_index;
        int right_index;
        int left_value;
        int right_value;
        int global_min;
        int _min_index;
      
        node_t(){
            left_index = inf;
            right_index = -inf;
            left_value = inf;
            right_value = inf;
            global_min = inf;
            _min_index = 0;
        }

        bool operator == (const node_t &other)const{
            return this->left_index == other.left_index &&
                   this->left_value == other.left_value &&
                   this->right_index == other.right_index &&
                   this->right_value == other.right_value &&
                   this->global_min == other.global_min &&
                   this->_min_index == other._min_index;
        }

        bool active(){
            return (*this == node_t()) == false;
        }

        void propagate(const lazy_t &lazy){
            if(this->active() == false){
                return ;
            }
            left_value = lazy.eval(left_index);
            right_value = lazy.eval(right_index);
            if(left_value < right_value){
                _min_index = left_index;
                global_min = left_value;
            }else{
                _min_index = right_index;
                global_min = right_value;
            }
        }

        node_t operator + (const node_t &other)const{
            node_t ans;
            if(this->global_min < other.global_min){
                ans.global_min = this->global_min;
                ans._min_index = this->_min_index;
            }else{
                ans.global_min = other.global_min;
                ans._min_index = other._min_index;
            }
            if(this->left_index < other.left_index){
                ans.left_index = this->left_index;
                ans.left_value = this->left_value;
            }else{
                ans.left_index = other.left_index;
                ans.left_value = other.left_value;
            }
            if(this->right_index > other.right_index){
                ans.right_index = this->right_index;
                ans.right_value = this->right_value;
            }else{
                ans.right_index = other.right_index;
                ans.right_value = other.right_value;
            }
            return ans;
        }
    };

    int n;
    vector<node_t> aint;
    vector<lazy_t> lazy;

    void build(int nod,int st,int dr){
        if(st == dr){
            aint[nod] = node_t();
            aint[nod].left_index = aint[nod].right_index = st;
            aint[nod]._min_index = st;
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid);
        build(nod * 2 + 1,mid + 1,dr);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void propagate(int nod,int st,int dr){
        if(st == dr || lazy[nod].is_valid() == false){
            return ;
        }

        aint[nod * 2].propagate(lazy[nod]);
        aint[nod * 2 + 1].propagate(lazy[nod]);
        lazy[nod * 2] = lazy[nod];
        lazy[nod * 2 + 1] = lazy[nod];
        lazy[nod] = lazy_t();
    }

    void deactivate(int nod,int st,int dr,int pos){
        propagate(nod,st,dr);

        if(dr < pos || st > pos){
            return ;
        }

        if(st == dr){
            aint[nod] = node_t();
            return ;
        }

        int mid = (st + dr) / 2;

        deactivate(nod * 2,st,mid,pos);
        deactivate(nod * 2 + 1,mid + 1,dr,pos);
        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update_min(int nod,int st,int dr,int l,int r,const lazy_t &value){
        propagate(nod,st,dr);
        if(aint[nod].active() == false || r < st || l > dr || (value.eval(aint[nod].left_index) >= aint[nod].left_value && value.eval(aint[nod].right_index) >= aint[nod].right_value)){
            return ;
        }

        if(l <= st && dr <= r && value.eval(aint[nod].left_index) <= aint[nod].left_value && value.eval(aint[nod].right_index) <= aint[nod].right_value){
            lazy[nod] = value;
            aint[nod].propagate(value);
            return ;
        }

        int mid = (st + dr) / 2;

        update_min(nod * 2,st,mid,l,r,value);
        update_min(nod * 2 + 1,mid + 1,dr,l,r,value);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

public:

    SegmentTree(int n){
        this->n = n;
        this->aint = vector<node_t>(4 * n + 5,node_t());
        this->lazy = vector<lazy_t>(4 * n + 5,lazy_t());
        build(1,1,n);
    }

    void deactivate(int pos){
        deactivate(1,1,n,pos);
    }

    void update_min(int l,int r,int a,int b){
        update_min(1,1,n,l,r,lazy_t(a,b));
    }

    pair<int,int> query(){
        return make_pair(aint[1].global_min,aint[1]._min_index);
    }

    bool active(){
        return aint[1].active();
    }
};

const int NMAX = 1e6;

int n;
int father[NMAX + 5];

bool active[NMAX + 5];
int dist[NMAX + 5];

int i32(){

    int ans;
    scanf("%d",&ans);

    return ans;
}

int main(){
    n = i32();

    for(int i = 1;i <= n;i++){
        father[i] = i32();
        active[i] = true;
        dist[i] = 1e9;
        father[i]++;
    }

    SegmentTree aint(n);

    int last_node = 1;
    dist[last_node] = 0;

    while(aint.active()){
        if(active[last_node]){
            if(last_node == n){
                printf("%d\n",dist[last_node]);
                return 0;
            }
            aint.deactivate(last_node);
            active[last_node] = false;
            if(active[father[last_node]]){
                dist[father[last_node]] = dist[last_node];
            }

            aint.update_min(1,last_node,-1,last_node + dist[last_node]);
            aint.update_min(last_node,n,1,-last_node + dist[last_node]);

            last_node = father[last_node];
            continue;
        }

        pair<int,int> tmp = aint.query();

        dist[tmp.second] = tmp.first;
        last_node = tmp.second;
    }

    printf("%d\n",dist[n]);

    return 0;

}
