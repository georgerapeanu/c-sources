#include <bits/stdc++.h>

using namespace std;

const int LGMAX = 30;

class SegmentTree{

    struct node_t{
        int lazy;
        int cnt_bit[LGMAX];
        vector<pair<int,int> > vals;

        node_t(){
            lazy = 0;
            for(int i = 0;i < LGMAX;i++){
                cnt_bit[i] = 0;
            }
            vals = {{(1 << LGMAX),0},{(1 << LGMAX) + 1,0}};
        }
        node_t(int val){
            lazy = 0;
            for(int i = 0;i < LGMAX;i++){
                cnt_bit[i] = ((val >> i) & 1);
            }
            vals = {{val,1},{(1 << LGMAX),0}};
        }

        node_t operator + (const node_t &other)const{
            node_t ans;
            ans.lazy = 0;
            for(int i = 0;i < LGMAX;i++){
                ans.cnt_bit[i] = this->cnt_bit[i] + other.cnt_bit[i];
            }
            
            ans.vals = this->vals;
            
            for(auto it:other.vals){
                ans.vals.push_back(it);
            }
            
            sort(ans.vals.begin(),ans.vals.end());

            int lst = 0;
            for(int i = 1; i < (int)ans.vals.size();i++){
                if(ans.vals[lst].first != ans.vals[i].first){
                    lst++;
                    ans.vals[lst] = ans.vals[i];
                }else{
                    ans.vals[lst].second += ans.vals[i].second;
                }
            }
            ans.vals.resize(2);
            return ans;
        }

        void propag(int lazy){
            this->lazy = lazy;

            for(int i = 0;i < LGMAX;i++){
                this->cnt_bit[i] -= vals[0].second * ((vals[0].first >> i) & 1);
            }

            this->vals[0].first = lazy;
            
            for(int i = 0;i < LGMAX;i++){
                this->cnt_bit[i] += vals[0].second * ((vals[0].first >> i) & 1);
            }
        }
    };

    int n;
    vector<node_t> aint;

    void build(int nod,int st,int dr,const vector<int> &v){
        if(st == dr){
            aint[nod] = node_t(v[st - 1]);
            return ;
        }
        
        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,v);
        build(nod * 2 + 1,mid + 1,dr,v);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void propag(int nod,int st,int dr){
        if(st == dr || aint[nod].lazy == 0){
            return ;
        }

        if(aint[nod * 2].vals[0].first < aint[nod].lazy){
            aint[nod * 2].propag(aint[nod].lazy);
        }
        if(aint[nod * 2 + 1].vals[0].first < aint[nod].lazy){
            aint[nod * 2 + 1].propag(aint[nod].lazy);
        }

        aint[nod].lazy = 0;
    }

    void update(int nod,int st,int dr,int l,int r,int val){
        propag(nod,st,dr);
        if(r < st || l > dr || val <= aint[nod].vals[0].first){
            return ;
        }
        
        if(l <= st && dr <= r && val < aint[nod].vals[1].first){
            aint[nod].propag(val);
            return ;
        }

        int mid = (st + dr) / 2;
        
        update(nod * 2,st,mid,l,r,val);
        update(nod * 2 + 1,mid + 1,dr,l,r,val);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    node_t query(int nod,int st,int dr,int l,int r){
        propag(nod,st,dr);

        if(dr < l || st > r){
            return node_t();
        }

        if(l <= st && dr <= r){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
        
    }

    public:

    SegmentTree(const vector<int> &v){
        this->n = v.size();
        this->aint = vector<node_t>(4 * this->n + 5);
        build(1,1,n,v);
    }

    void update(int l,int r,int val){
        update(1,1,n,l,r,val);
    }

    int query(int l,int r,int val){
        node_t ans = query(1,1,n,l,r);

        int xo = val;

        for(int i = 0;i < LGMAX;i++){
            if(ans.cnt_bit[i] % 2 == 1){
                xo ^= (1 << i);
            }
        }

        if(xo == 0){
            return 0;
        }

        int h = LGMAX - 1;

        while((xo >> h) == 0){
            h--;
        }

        return ans.cnt_bit[h] + ((val ^ xo) < val);
    }
};

int n;
int q;

int main(){

    scanf("%d %d",&n,&q);

    vector<int> v(n);

    for(auto &it:v){
        scanf("%d",&it);
    }

    SegmentTree aint(v);

    while(q--){
        int t,l,r,x;
        
        scanf("%d %d %d %d",&t,&l,&r,&x);

        if(t == 1){
            aint.update(l,r,x);
        }else{
            printf("%d\n",aint.query(l,r,x));
        }
    }

    return 0;
}
