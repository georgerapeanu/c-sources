#include <bits/stdc++.h>

using namespace std;

class SegmentTree{
    struct node_t{
        int active;
        long long sum;
        long long sum_active;
        long long lazy;

        node_t operator + (const node_t &other)const{
            node_t ans;
            ans.active = this->active + other.active;
            ans.sum = this->sum + other.sum;
            ans.sum_active = this->sum_active + other.sum_active;
            ans.lazy = 0;
            return ans;
        }

        void propagate(int lazy,int st,int dr){
            this->lazy += lazy;
            this->sum += lazy * (dr - st + 1);
            this->sum_active += active * lazy;
        }

        node_t(){
            active = sum = sum_active = lazy = 0;
        }
    };

    int n;
    vector<node_t> aint;

    void propagate(int nod,int st,int dr){
        if(st == dr){
            return ;
        }
        int mid = (st + dr) / 2;
        aint[nod * 2].propagate(aint[nod].lazy,st,mid);
        aint[nod * 2 + 1].propagate(aint[nod].lazy,mid + 1,dr);
        aint[nod].lazy = 0;
    }

    void activate(int nod,int st,int dr,int pos,int value){
        propagate(nod,st,dr);
        if(dr < pos || st > pos){
            return ;
        }
        if(st == dr){
            aint[nod].active = value;
            aint[nod].sum_active = aint[nod].sum * value;
            return ;
        }

        int mid = (st + dr) / 2;

        activate(nod * 2,st,mid,pos,value);
        activate(nod * 2 + 1,mid + 1,dr,pos,value);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update(int nod,int st,int dr,int l,int r,int value){
        propagate(nod,st,dr);
        if(dr < l || st > r){
            return;
        }
        if(l <= st && dr <= r){
            aint[nod].propagate(value,st,dr);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,l,r,value);
        update(nod * 2 + 1,mid + 1,dr,l,r,value);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    node_t query(int nod,int st,int dr,int l,int r){
        propagate(nod,st,dr);

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

    SegmentTree(int n){
        this->n = n;
        this->aint = vector<node_t>(4 * n + 5);
    }

    void activate(int pos,int value){
        activate(1,1,n,pos,value);
    }

    void update(int l,int r,int val){
        update(1,1,n,l,r,val);
    }

    long long query(int l,int r){
        return query(1,1,n,l,r).sum_active;
    }
};

const int NMAX = 2e5;

int n;
int v[NMAX + 5];
int last[NMAX + 5][2];

int main(){

    scanf("%d",&n);

    SegmentTree aint(n);

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);

        ans += aint.query(last[v[i]][1] + 1,i);

        if(last[v[i]][1]){
            if(last[v[i]][0]  + 1 <= last[v[i]][1] - 1){
                aint.update(last[v[i]][0] + 1,last[v[i]][1] - 1,-1);
            }
            aint.activate(last[v[i]][1],0);
        }

        last[v[i]][0] = last[v[i]][1];
        last[v[i]][1] = i;

        if(last[v[i]][0]  + 1 <= last[v[i]][1] - 1){
            aint.update(last[v[i]][0] + 1,last[v[i]][1] - 1,1);
        }
        aint.activate(last[v[i]][1],1);
    }

    printf("%lld\n",ans);

    return 0;
}

