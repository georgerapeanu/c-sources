#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

class SegmentTree{

    struct node_t{
        long long val;
        long long lazy;

        void propag(long long lazy_value){
            lazy += lazy_value;
            val += lazy_value;
        }

        node_t operator + (const node_t &other)const{
            node_t ans;
            ans.val = max(this->val,other.val);
            ans.lazy = 0;
            return ans;
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

    void update(int nod,int st,int dr,int l,int r,long long val){
        propag(nod,st,dr);
        if(r < st || dr < l){
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

    node_t query(int nod,int st,int dr,int l,int r){
        propag(nod,st,dr);
        if(r < st || dr < l){
            return {-(long long)1e18,0};
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
        aint = vector<node_t>(4 * n + 5);
    }

    void update(int l,int r,long long val){
        update(1,1,n,l,r,val);
    }

    void update(int pos,long long val){
        update(1,1,n,pos,pos,val);
    }

    long long query(int l,int r){
        return query(1,1,n,l,r).val;
    }
};

int n,m;
int a[NMAX + 5];
int b[NMAX + 5];

int main(){

    while(scanf("%d %d",&n,&m) != EOF){
        SegmentTree aint(n);
        SegmentTree sum_b(n);

        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
            aint.update(i,a[i]);
        }

        long long sum = 0;
        for(int i = 1;i <= n;i++){
            scanf("%d",&b[i]);
            sum += b[i];
            sum_b.update(i,n,b[i]);
            aint.update(i,-sum);
        }

        while(m--){
            int t;
            scanf("%d",&t);
            if(t == 1){
                int pos,val;
                scanf("%d %d",&pos,&val);
                aint.update(pos,-a[pos]);
                a[pos] = val;
                aint.update(pos,a[pos]);
            }
            else if(t == 2){
                int pos,val;
                scanf("%d %d",&pos,&val);
                aint.update(pos,n,+b[pos]);
                sum_b.update(pos,n,-b[pos]);
                b[pos] = val;
                aint.update(pos,n,-b[pos]);
                sum_b.update(pos,n,+b[pos]);
            }
            else{
                int pos;
                scanf("%d",&pos);
            //    cerr << "deb " << aint.query(1,pos) << " " << sum_b.query(pos,pos) << endl;
                printf("%lld\n",max(0LL,aint.query(1,pos)) + sum_b.query(pos,pos));
            }
        }
    }

    return 0;
}
