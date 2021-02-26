#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }

    return p;
}

struct node_t{
    int value;
    long long sum;

    node_t(){
        value = 0;
        sum = 0;
    }

    node_t operator + (const node_t &other)const{
        node_t ans;
        ans.value = max(this->value,other.value);
        ans.sum = this->sum + other.sum;
        return ans;
    }

};

class SegmentTree{


    int n;
    vector<node_t> aint;

    void build(int nod,int st,int dr,const vector<int> &v){
        if(st == dr){
            aint[nod].value = v[st - 1];
            aint[nod].sum = v[st - 1];
            return ;
        }
        int mid = (st + dr) / 2;
        build(nod * 2,st,mid,v);
        build(nod * 2 + 1,mid + 1,dr,v);
        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update(int nod,int st,int dr,int pos,int val){
        if(st > pos || dr < pos){
            return ;
        }
        if(st == dr){
            aint[nod].value = val;
            aint[nod].sum = val;
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val);
        update(nod * 2 + 1,mid + 1,dr,pos,val);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    node_t query(int nod,int st,int dr,int l,int r){
        if(r < st || l > dr){
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
        this->n = (int)v.size();
        this->aint = vector<node_t>(4 * n + 5);
        build(1,1,n,v);
    }

    void update(int pos,int val){
        update(1,1,n,pos,val);
    }

    node_t query(int l,int r){
        return query(1,1,n,l,r);
    }
};

int n,q;
vector<int> v;

int main(){
    
    scanf("%d %d",&n,&q);
    v = vector<int>(n);

    for(auto &it:v){
        scanf("%d",&it);
    }

    SegmentTree aint(v);

    while(q--){
        int t,l,r;
        scanf("%d %d %d",&t,&l,&r);

        if(t == 1){
            aint.update(l,r);
        }else{
            node_t tmp = aint.query(l,r);

            tmp.sum -= tmp.value;
            if(tmp.sum >= tmp.value - 1){
                printf("%d\n",int(2LL * (tmp.sum + tmp.value) % MOD));
            }else{
                int default_bucket = tmp.value / (tmp.sum + 1);
                int bonus = (tmp.value % (tmp.sum + 1));
                int ans = 0;
                ans = add(ans,mult(2,tmp.sum));
                ans = add(ans,mult(lgpow(2,default_bucket),tmp.sum + 1 - bonus));
                ans = add(ans,mult(lgpow(2,default_bucket + 1),bonus));
                printf("%d\n",ans);
            }

        }
    }

    return 0;
}
