#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int mod;
vector<int> desc;
int phi;

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = 1LL * b * p % mod;
        }

        b = 1LL * b * b % mod;
        e >>= 1;
    }

    return p;
}

void init_smecherie(){
    int tmp_mod = mod;

    phi = mod;

    for(int k = 2;1LL * k * k <= tmp_mod;k++){
        if(tmp_mod % k == 0){
            desc.push_back(k);
            phi = (phi / k) * (k - 1);
            while(tmp_mod % k == 0){
                tmp_mod /= k;
            }
        }
    }

    if(tmp_mod != 1){
        phi = (phi / tmp_mod) * (tmp_mod - 1);
        desc.push_back(tmp_mod);
    }
}

class IntSmecher{
public:
    
    int free_val;

    vector<pair<int,int> > fact;

    IntSmecher(int a){
        if(a == 0){
            printf("bag pula\n");
        }
        fact.resize(desc.size());
        for(int i = 0;i < (int)desc.size();i++){
            fact[i].first = desc[i];
            while(a && a % desc[i] == 0){
                fact[i].second++;
                a /= desc[i];
            }
        }
        this->free_val = a;
    }   

    IntSmecher(){
    } 
    
    IntSmecher operator / (const IntSmecher &other)const{
        IntSmecher ans = *this;
        ans.free_val = 1LL * ans.free_val * lgpow(other.free_val,phi - 1) % mod;
        for(int i = 0;i < (int)desc.size();i++){
            ans.fact[i].second -= other.fact[i].second;
        }
        return ans;
    }

    IntSmecher operator * (const IntSmecher &other)const{
        IntSmecher ans = *this;
        ans.free_val = 1LL * ans.free_val * other.free_val % mod;
        for(int i = 0;i < (int)desc.size();i++){
            ans.fact[i].second += other.fact[i].second;
        }
        return ans;
    }

    int toInt(){
        int ans = this->free_val;

        for(auto it:fact){
            ans = 1LL * ans * lgpow(it.first,it.second) % mod;
        }

        return ans;
    }
};

int n;

int aint[4 * NMAX + 5];
IntSmecher v[4 * NMAX + 5];
int lazy[4 * NMAX + 5];
IntSmecher lazy2[4 * NMAX + 5];
IntSmecher base;

void build(int nod,int st,int dr){
    lazy[nod] = 1;
    lazy2[nod] = base;

    if(st == dr){
        int val;
        scanf("%d",&val);
        v[st] = IntSmecher(val);
        aint[nod] = val % mod;
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = (aint[nod * 2] + aint[nod * 2 + 1]) % mod;
}

void propag(int nod,int st,int dr){
    if(lazy[nod] == 1){
        return ;
    }

    if(st == dr){
        v[st] = v[st] * lazy2[nod];
        lazy[nod] = 1;
        lazy2[nod] = base;
        return ;
    }

    aint[2 * nod] = 1LL * aint[2 * nod] * lazy[nod] % mod;
    aint[2 * nod + 1] = 1LL * aint[2 * nod + 1] * lazy[nod] % mod;
    lazy[2 * nod] = 1LL * lazy[2 * nod] * lazy[nod] % mod;
    lazy[2 * nod + 1] = 1LL * lazy[2 * nod + 1] * lazy[nod] % mod;
    lazy2[2 * nod] = lazy2[nod] * lazy2[nod * 2];
    lazy2[2 * nod + 1] = lazy2[nod] * lazy2[2 * nod + 1];
    lazy2[nod] = base;
    lazy[nod] = 1;
}

void update_mult(int nod,int st,int dr,int S,int D,const int &val,const IntSmecher &vval){
    propag(nod,st,dr);

    if(dr < S || st > D){
        return ;
    }

    if(S <= st && dr <= D){
        lazy2[nod] = lazy2[nod] * vval;
        lazy[nod] = 1LL * lazy[nod] * val % mod;
        aint[nod] = 1LL * aint[nod] * val % mod;
        return ;
    }

    int mid = (st + dr) / 2;

    update_mult(nod * 2,st,mid,S,D,val,vval);
    update_mult(nod * 2 + 1,mid + 1,dr,S,D,val,vval);

    aint[nod] = (aint[2 * nod] + aint[2 * nod + 1]) % mod;
}

void update_div(int nod,int st,int dr,int pos,int val){
    propag(nod,st,dr);
    if(dr < pos || st > pos){
        return ;
    }

    if(st == dr){
        v[pos] = v[pos] / IntSmecher(val);
        aint[nod] = v[pos].toInt();
        return ;
    }

    int mid = (st + dr) / 2;
    update_div(nod * 2,st,mid,pos,val);
    update_div(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = (aint[2 * nod] + aint[2 * nod + 1]) % mod;
}

int query(int nod,int st,int dr,int S,int D){
    propag(nod,st,dr);

    if(dr < S || st > D){
        return 0;
    }

    if(S <= st && dr <= D){
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return (query(nod * 2,st,mid,S,D) + query(nod * 2 + 1,mid + 1,dr,S,D)) % mod;
}

int main(){

    scanf("%d %d",&n,&mod);

    init_smecherie();

    base = IntSmecher(1);

    build(1,1,n);

    int q;

    scanf("%d",&q);

    while(q--){
        int t;
        scanf("%d",&t);

        if(t == 1){
            int l,r,x;
            scanf("%d %d %d",&l,&r,&x);
            update_mult(1,1,n,l,r,x,IntSmecher(x));
        }
        else if(t == 2){
            int l,v;
            scanf("%d %d",&l,&v);
            update_div(1,1,n,l,v);
        }
        else if(t == 3){
            int l,r;
            scanf("%d %d",&l,&r);
            printf("%d\n",query(1,1,n,l,r));
        }
    }

    return 0;
}
