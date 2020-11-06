#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

class SegmentTree{
private:
    vector<int> aint;
    vector<int> l;
    vector<int> r;
    int n;
    int root;

    int new_node(int val = 1,int ll = 0,int rr = 0){
        aint.push_back(val);
        l.push_back(ll);
        r.push_back(rr);
        return (int)aint.size() - 1;
    }

    int build(int st,int dr){
        if(st == dr){
            return new_node();
        }

        int mid = (st + dr) / 2;

        int tmp_l = build(st,mid);
        int tmp_r = build(mid + 1,dr);
        
        int nod = new_node(1,tmp_l,tmp_r);

        return nod;
    }

    int update(int nod,int st,int dr,int le,int ri,int val){

        if(ri < st || le > dr){
            return nod;
        }

        if(le <= st && dr <= ri){
            int tmp = new_node(1LL * aint[nod] * val % MOD,l[nod],r[nod]);     
            return tmp;
        }

        int mid = (st + dr) / 2;

        int a = update(l[nod],st,mid,le,ri,val);
        int b = update(r[nod],mid + 1,dr,le,ri,val);
    
        int tmp = new_node(aint[nod],a,b);

        return tmp;
    }

    int query(int nod,int st,int dr,int pos,int val){
        if(st > pos || dr < pos){
            return 1;
        }

        if(st == dr){
            return 1LL * aint[nod] * val % MOD;
        }

        int mid = (st + dr) / 2;

        int a = query(l[nod],st,mid,pos,1LL * aint[nod] * val % MOD);
        int b = query(r[nod],mid + 1,dr,pos,1LL * aint[nod] * val % MOD);

        return a * b;
    }

public:

    void afis(){
        return ;
        for(auto it:aint)printf("%d ",it);printf("\n");
        for(auto it:l)printf("%d ",it);printf("\n");
        for(auto it:r)printf("%d ",it);printf("\n");
    }

    SegmentTree(int n){
        new_node();
        this->n = n;
        this->root = build(1,n);
    }

    int update(int l,int r,int val){
        assert(l <= r);
        return root = update(root,1,n,l,r,val); 
    }
    
    int query(int root,int pos){
        return query(root,1,n,pos,1);
    }
};

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }

    return p;
}

int n;
int a[100005];
int lo[200005];
int roots[100005];

vector<pair<int,int> > s[200005];

int main() {

    for(int i = 2;i <= 200000;i++){
        if(lo[i] == 0){
            for(int j = i;j <= 200000;j += i){
                if(lo[j] == 0){
                    lo[j] = i;
                }
            }
        }
    }

    scanf("%d",&n);

    SegmentTree aint(n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        vector<pair<int,int> > primes;
        while(a[i] != 1){
            if((int)primes.size() == 0 || primes.back().first != lo[a[i]]){
                primes.push_back({lo[a[i]],0});
            }
            a[i] /= lo[a[i]];
            primes.back().second++;
        }
        aint.afis();
        for(auto it:primes){
            int lst = i,lst_pow = 0;
            while(s[it.first].size() && s[it.first].back().second <= it.second){
                aint.update(s[it.first].back().first + 1,lst,lgpow(it.first,MOD - 1 - lst_pow));
                lst = s[it.first].back().first;
                lst_pow = s[it.first].back().second;
                s[it.first].pop_back();
            }
            int tmp = (s[it.first].size() ? s[it.first].back().first + 1:1);
            aint.update(tmp,lst,lgpow(it.first,MOD - 1 - lst_pow));
            roots[i] = aint.update(tmp,i,lgpow(it.first,it.second));
            s[it.first].push_back({i,it.second});
        }
        aint.afis();
    }

    int q;

    scanf("%d",&q);

    int last = 0;

    while(q--){
        int l,r;
        scanf("%d %d",&l,&r);
        l = (last + l) % n + 1;
        r = (last + r) % n + 1;
        if(l > r){
            swap(l,r);
        }
        printf("%d\n",last = aint.query(roots[r],l));
    }

    return 0;
}
