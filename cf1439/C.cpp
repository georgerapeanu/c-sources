#include <bits/stdc++.h>

using namespace std;

struct node_t{
    long long sum;
    int left_value;
    int right_value;
    int lazy;
    int len;

    node_t operator + (const node_t &other)const{
        node_t ans;
        ans.sum = this->sum + other.sum;
        ans.left_value = this->left_value;
        ans.right_value = other.right_value;
        ans.len = this->len + other.len;
        ans.lazy = 0;
        return ans;
    }

    void propagate(int val){
        sum = 1LL * len * val;
        left_value = right_value = val;
        lazy = val;
    }

    node_t(int val){
        sum = val;
        left_value = right_value = val;
        len = 1;
        lazy = 0;
    }

    node_t(){
        sum = 0;
        left_value = right_value = 0;
        lazy = 0;
        len = 0;
    }
};

class SegmentTree{
    int n;
    vector<node_t> aint;

    void build(int nod,int st,int dr,const vector<int> &values){
        if(st == dr){
            aint[nod] = node_t(values[st - 1]);
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,values);
        build(nod * 2 + 1,mid + 1,dr,values);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void propagate(int nod,int st,int dr){
        if(aint[nod].lazy == 0 || st == dr){
            return ;
        }

        aint[nod * 2].propagate(aint[nod].lazy);
        aint[nod * 2 + 1].propagate(aint[nod].lazy);
        aint[nod].lazy = 0;
    }

    void update(int nod,int st,int dr,int l,int r,int value){
        propagate(nod,st,dr);

        if(r < st || l > dr || aint[nod].right_value >= value){
            return ;
        }
        
        if(l <= st && dr <= r && aint[nod].left_value <= value){
            aint[nod].propagate(value);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,l,r,value);
        update(nod * 2 + 1,mid + 1,dr,l,r,value);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    int find_first_leq(int nod,int st,int dr,int l,int r,int value){
        propagate(nod,st,dr);

        if(r < st || l > dr || aint[nod].right_value > value){
            return 1e9;
        }

        if(l <= st && dr <= r && aint[nod].left_value <= value){
            return st;
        }

        int mid = (st + dr) / 2;

        return min(find_first_leq(nod * 2,st,mid,l,r,value),find_first_leq(nod * 2 + 1,mid + 1,dr,l,r,value));
    }

    node_t find_segment(int nod,int st,int dr,int l,int r,int value){
        propagate(nod,st,dr);
        if(r < st || l > dr){
            return node_t();
        }

        if(l <= st && dr <= r && aint[nod].left_value > value){
            return node_t();
        }

        if(l <= st && dr <= r && aint[nod].sum <= value){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        node_t ans;

        ans = find_segment(nod * 2,st,mid,l,r,value);
        if(ans.sum <= value && ans.len == max(min(mid,r) - max(st,l) + 1,0)){
            ans = ans + find_segment(nod * 2 + 1,mid + 1,dr,l,r,value - ans.sum);
        }
        return ans;
    }

    public:

    SegmentTree(const vector<int> &values){
        this->n = (int)values.size();
        this->aint = vector<node_t>(4 * n + 5);
        build(1,1,n,values);
    }

    void update(int x,int y){
        update(1,1,n,1,x,y);
    }

    int find_first_leq(int x,int value){
        return find_first_leq(1,1,n,x,n,value);
    }

    node_t find_segment(int x,int value){
        return find_segment(1,1,n,x,n,value);
    }
};

int main(){

    int n,q;
    vector<int> v;

    scanf("%d %d",&n,&q);

    v = vector<int>(n,0);

    for(auto &it:v){
        scanf("%d",&it);
    }

    SegmentTree aint(v);

    while(q--){
        int t,x,y;
        
        scanf("%d %d %d",&t,&x,&y);

        if(t == 1){
            aint.update(x,y);
        }
        else{
            int ans = 0;
            while(true){
                x = aint.find_first_leq(x,y);
                if(x > n){
                    break;
                }
                node_t tmp = aint.find_segment(x,y);
                ans += tmp.len;
                x += tmp.len;
                y -= tmp.sum;
            }
            printf("%d\n",ans);
        }
    }

    return 0;
}
