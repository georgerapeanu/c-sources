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

int scad(int a,int b){
    a -= b;

    if(a < 0){
        a += MOD;
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

struct lazy_t{
    int v[3];

    lazy_t(){
        v[0] = v[1] = v[2] = -1;
    }

    lazy_t(int a,int b,int c){
        v[0] = a;
        v[1] = b;
        v[2] = c;
    }

    void apply_lazy(const lazy_t &other){
        for(int h = 0;h < 3;h++){
            if(other.v[h] != -1){
                this->v[h] = other.v[h];
            }
        }
    }
};

class SegmentTree{

    struct node_t{
        int sum[1 << 3];
        
        node_t(){
            memset(sum,0,sizeof(sum));
        }

        node_t operator + (const node_t &other)const{
            node_t ans;
            for(int conf = 0;conf < (1 << 3);conf++){
                ans.sum[conf] = add(this->sum[conf],other.sum[conf]);
            }
            return ans;
        }

        void apply_lazy(const lazy_t &lazy){
            for(int h = 0;h < 3;h++){
                if(lazy.v[h] != -1){
                    for(int conf = (1 << h);conf < (1 << 3);conf = ((conf + 1) | (1 << h))){
                        sum[conf] = mult(lazy.v[h],sum[conf ^ (1 << h)]);         
                    }
                }
            }
        }
    };

    int n;
    vector<node_t> aint;
    vector<lazy_t> lazy;

    void apply_lazy(int nod,int st,int dr){
        if(st == dr){
            return ;
        }
        aint[nod * 2].apply_lazy(lazy[nod]);
        aint[nod * 2 + 1].apply_lazy(lazy[nod]);
        lazy[nod * 2].apply_lazy(lazy[nod]);
        lazy[nod * 2 + 1].apply_lazy(lazy[nod]);
        lazy[nod] = lazy_t();
    }

    void build(int nod,int st,int dr){
        if(st == dr){
            aint[nod] = node_t();
            aint[nod].sum[0] = 1;
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid);
        build(nod * 2 + 1,mid + 1,dr);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update(int nod,int st,int dr,int l,int r,const lazy_t &_lazy){
        apply_lazy(nod,st,dr);

        if(r < st || l > dr){
            return ;
        }

        if(l <= st && dr <= r){
            aint[nod].apply_lazy(_lazy);
            lazy[nod].apply_lazy(_lazy);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,l,r,_lazy);
        update(nod * 2 + 1,mid + 1,dr,l,r,_lazy);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    node_t query(int nod,int st,int dr,int l,int r){
        apply_lazy(nod,st,dr);

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

    SegmentTree(int n){
        this->n = n;
        this->aint = vector<node_t>(4 * n + 5);
        this->lazy = vector<lazy_t>(4 * n + 5);
        build(1,1,n);
    }

    void update(int st,int dr,const lazy_t &lazy){
        this->update(1,1,n,st,dr,lazy);
    }

    int query(int l,int r){
        return aint[1].sum[(1 << 3) - 1];
    }
};

FILE *f = fopen("hipersum.in","r");
FILE *g = fopen("hipersum.out","w");

const int NMAX = 1e5;
const int LGMAX = 30;

int n;
int v[NMAX + 5];

vector<int> min_stack = {0};
vector<int> max_stack = {0};

int last_0[LGMAX + 1];
int last_1[LGMAX + 1];

SegmentTree aint(1);

/*
int _min[NMAX + 5];
int _max[NMAX + 5];
*/
int _and[NMAX + 5];
int _or[NMAX + 5];
void update_min(int l,int r,int val){
    /*
    for(int i = l;i <= r;i++){
        _min[i] = val;
    }
    */
    aint.update(l,r,lazy_t(val,-1,-1));
}

void update_max(int l,int r,int val){
    /*
    for(int i = l;i <= r;i++){
        _max[i] = val;
    }
    */
    aint.update(l,r,lazy_t(-1,val,-1));
}

int query(int l,int r){
    /*
    int ans = 0;

    for(int i = l;i <= r;i++){
        ans = add(ans,mult(mult(_min[i],_max[i]),mult(__and[i],__or[i])));
    }
    return ans;
    */
    return aint.query(l,r);
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    return ans;
}

int main(){

    n = i32();

    aint = SegmentTree(n);

    for(int i = 1;i <= n;i++){
        v[i] = i32();
        _and[i] = (1 << (LGMAX + 1)) - 1;
        _or[i] = 0;
    }

    int ans = 0;

    for(int i = 1;i <= n;i++){
        while((int)min_stack.size() > 1 && v[min_stack.back()] >= v[i]){
           min_stack.pop_back();
        }
        update_min(min_stack.back() + 1,i,v[i]);
        min_stack.push_back(i);

        while((int)max_stack.size() > 1 && v[max_stack.back()] <= v[i]){
            max_stack.pop_back();
        }
        update_max(max_stack.back() + 1,i,v[i]);
        max_stack.push_back(i);

        int furthest_update = i;

        for(int h = 0;h <= LGMAX;h++){
            if((v[i] >> h) & 1){
                for(int j = last_1[h] + 1;j <= i;j++){
                    _or[j] += (1 << h);
                }
                furthest_update = min(last_1[h] + 1,furthest_update);
                last_1[h] = i;
            }else{
                for(int j = last_0[h] + 1;j <= i;j++){
                    _and[j] -= (1 << h);
                }
                furthest_update = min(last_0[h] + 1,furthest_update);
                last_0[h] = i;    
            }
        }

        for(int j = furthest_update;j <= i;j++){
            aint.update(j,j,lazy_t(-1,-1,mult(_or[j],_and[j])));
        }

        ans = add(ans,query(1,i));
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}

///TODO try to brute the bits, because each position changes at most 20 times and they are sc
