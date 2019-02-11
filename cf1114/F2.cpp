#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 4e5;
const int QMAX = 2e5;
const int VMAX = 300;

//tested on http://codeforces.com/contest/1043/problem/F
///tested on https://codeforces.com/contest/1078/problem/B
///kinda
///teste on https://infoarena.ro/problema/100m for real
class ModularInt {

private:
    static const int MOD = 1e9 + 7;

    int val;

public:

    ModularInt() {
        val = 0;
    }

    ModularInt(int a) {
        val = (a % MOD + MOD) % MOD;
    }

    ModularInt operator + (const ModularInt &other)const {
        ModularInt ans(this->val + other.val);

        if(ans.val >= MOD) {
            ans.val -= MOD;
        }

        return ans;
    }

    ModularInt operator - (const ModularInt &other)const {
        ModularInt ans(this->val - other.val);

        if(ans.val < 0) {
            ans.val += MOD;
        }

        return ans;
    }

    ModularInt operator * (const ModularInt &other)const {
        return ModularInt(1LL * this->val * other.val % MOD);
    }

    ModularInt operator / (const ModularInt &other)const {
        ModularInt ans = 1;
        ModularInt base(other.val);
        int e = MOD - 2;

        while(e) {
            if(e & 1) {
                ans = ans * base;
            }
            base = base * base;
            e >>= 1;
        }

        ans = (*this) * ans;

        return ans;
    }

    bool operator == (const ModularInt &other)const {
        return this->val == other.val;
    }

    bool operator != (const ModularInt &other) {
        return this->val != other.val;
    }

    bool operator < (const ModularInt &other) {
        return this->val < other.val;
    }

    ModularInt pw(int e) {
        ModularInt p = 1;
        ModularInt b = *this;

        while(e) {
            if(e & 1) {
                p = p * b;
            }
            b = b * b;
            e >>= 1;
        }

        return p;
    }

    bool is0() {
        return val == 0;
    }

    int toInt() {
        return val;
    }

    void print() {
        printf("%d\n",val);
    }
};

struct data_t {
    ModularInt p;
    long long mask;

    bool operator == (const data_t &other)const {
        return this->p == other.p && this->mask == other.mask;
    }

    data_t(ModularInt p = 1,long long mask = 0) {
        this->p = p;
        this->mask = mask;
    }

    data_t join(const data_t &other)const {
        return data_t(this->p * other.p, this->mask | other.mask);
    }

    data_t change(const data_t &other)const {
        return data_t(this->p * other.p, this->mask | other.mask);
    }
};

///tested on https://infoarena.ro/problema/arbint
///tested on https://infoarena.ro/problema/parcele
///0-indexed;

template<typename tp>
class SegmentTree {
private:

    bool enforce_throws;
    int n;
    tp neutral_aint;
    tp neutral_lazy;
    vector<tp> aint;
    vector<tp> lazy;

    ///change these

    tp join(tp a,tp b) {
        return a.join(b);
    }

    tp change(tp a,tp b) { ///change a by operating it with b
        return a.change(b);
    }

    void propag(int nod,int st,int dr) {
        if(st == dr || lazy[nod] == neutral_lazy) {
            return;
        }

        int mid = (st + dr) / 2;

        lazy[2 * nod] = change(lazy[2 * nod],lazy[nod]);
        lazy[2 * nod + 1] = change(lazy[2 * nod + 1],lazy[nod]);
        aint[2 * nod] = tp(aint[2 * nod].p * lazy[nod].p.pw(mid - st + 1),aint[2 * nod].mask | lazy[nod].mask);
        aint[2 * nod + 1] = tp(aint[2 * nod + 1].p * lazy[nod].p.pw(dr - mid),aint[2 * nod + 1].mask | lazy[nod].mask);
        lazy[nod] = neutral_lazy;
    }

    ///

    void build(int nod,int st,int dr,vector<tp> &base) {
        lazy[nod] = neutral_lazy;
        aint[nod] = neutral_aint;

        if(st == dr) {
            aint[nod] = base[st];
            return;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,base);
        build(nod * 2 + 1,mid + 1,dr,base);
        aint[nod] = join(aint[2 * nod],aint[2 * nod + 1]);
    }


    void update(int nod,int st,int dr,int S,int D,tp val) {
        propag(nod,st,dr);

        if(D < st || S > dr) {
            return ;
        }

        if(S <= st && dr <= D) {
            lazy[nod] = change(lazy[nod],val);
            aint[nod].mask |= val.mask;
            aint[nod].p = aint[nod].p * val.p.pw(dr - st + 1);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,S,D,val);
        update(nod * 2 + 1,mid + 1,dr,S,D,val);

        aint[nod] = join(aint[2 * nod],aint[2 * nod + 1]);
    }

    tp query(int nod,int st,int dr,int S,int D) {
        propag(nod,st,dr);

        if(D < st || S > dr) {
            return neutral_aint;
        }

        if(S <= st && dr <= D) {
            return aint[nod];
        }

        int mid = (st + dr) / 2;
        return join(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
    }

public:

    SegmentTree(vector<tp> &base,tp neutral_aint = tp(1,0),tp neutral_lazy = tp(1,0),bool enforce_throws = true) {
        this->enforce_throws = enforce_throws;
        this->n = base.size();
        this->neutral_aint = neutral_aint;
        this->neutral_lazy = neutral_lazy;
        aint.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
        build(1,0,n - 1,base);
    }

    SegmentTree(int n,tp neutral_aint = tp(1,0),tp neutral_lazy = tp(1,0),bool enforce_throws = true) {
        this->enforce_throws = enforce_throws;
        this->n = n;
        this->neutral_aint = neutral_aint;
        this->neutral_lazy = neutral_lazy;
        aint = vector<tp>(4 * n + 1,neutral_aint);
        lazy = vector<tp>(4 * n + 1,neutral_lazy);
    }

    void update(int st,int dr,tp val) {
        if(enforce_throws && (st > dr || st < 0 || dr >= n)) {
            throw runtime_error("invalid update");
        }
        update(1,0,n - 1,st,dr,val);
    }

    tp query(int st,int dr) {
        if(enforce_throws && (st > dr || st < 0 || dr >= n)) {
            throw runtime_error("invalid update");
        }

        return query(1,0,n - 1,st,dr);
    }

    tp overall() {
        return aint[1];
    }

    // void print(){
    // for(auto it:aint){
    // printf("%d ",it);
    // }
    // printf("\n");
    // }
};

int n,q;

vector<data_t> base;
vector<int> primes;

bool sieve[VMAX + 5];
char c[NMAX + 5];

long long mask[VMAX + 5];

vector<ModularInt> ch;

int main() {



    scanf("%d %d",&n,&q);

    sieve[0] = sieve[1] = true;

    for(int i = 2; i <= VMAX; i++) {
        if(sieve[i] == false) {
            primes.push_back(i);
            ch.push_back(ModularInt(i - 1) / ModularInt(i));
            for(int j = i; j <= VMAX; j += i) {
                sieve[j] = true;
                mask[j] |= (1LL << ((int)primes.size() - 1));
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        base.push_back(data_t(ModularInt(val),mask[val]));
    }

    SegmentTree<data_t> aint(base, {ModularInt(1),0}, {ModularInt(1),0},false);

    while(q--) {
        scanf("%s",c);

        if(c[0] == 'T') {
            int l,r;
            scanf("%d %d\n",&l,&r);
            l--;
            r--;
            data_t tmp = aint.query(l,r);
            ModularInt ans = tmp.p;
            for(int i = 0; i < (int)primes.size(); i++) {
                if((tmp.mask >> i) & 1) {
                    ans = ans *ch[i];
                }
            }
            printf("%d\n",ans.toInt());
        }
        else {
            int l,r,x;
            scanf("%d %d %d\n",&l,&r,&x);
            l--;
            r--;
            aint.update(l,r,data_t(ModularInt(x),mask[x]));
        }
    }

    return 0;
}
