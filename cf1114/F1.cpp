#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 4e5;
const int QMAX = 2e5;
const int VMAX = 300;
const int MOD = 1e9 + 7;

pair<int,long long> aint[4 * NMAX + 5];
pair<int,long long> lazy[4 * NMAX + 5];

pair<int,long long> v[4 * NMAX + 5];


long long mask[VMAX + 5];
bool ciur[VMAX + 5];

char c[NMAX + 5];

void build(int nod,int st,int dr) {
    lazy[nod] = {1,0};
    aint[nod] = {1,0};

    if(st == dr) {
        aint[nod] = v[st];
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod].first = 1LL * aint[nod * 2].first * aint[2 * nod + 1].first % MOD;
    aint[nod].second = aint[nod * 2].second | aint[2 * nod + 1].second;
}

int lgpow(int b,int e) {
    int p = 1;

    while(e) {
        if(e & 1) {
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}

void propag(int nod,int st,int dr) {
    if(st == dr || lazy[nod] == make_pair(1,0LL)) {
        return ;
    }

    int mid = (st + dr) / 2;

    lazy[2 * nod] = make_pair(1LL * lazy[nod].first * lazy[2 * nod].first % MOD,lazy[nod].second | lazy[2 * nod].second);
    lazy[2 * nod + 1] = make_pair(1LL * lazy[nod].first * lazy[2 * nod + 1].first % MOD,lazy[nod].second | lazy[2 * nod + 1].second);
    aint[2 * nod] = make_pair(1LL * lgpow(lazy[nod].first,mid - st + 1) * aint[2 * nod].first % MOD,lazy[nod].second | aint[2 * nod].second);
    aint[2 * nod + 1] = make_pair(1LL * lgpow(lazy[nod].first,dr - mid) * aint[2 * nod + 1].first % MOD,lazy[nod].second | aint[2 * nod + 1].second);

    lazy[nod] = {1,0};
}

void update(int nod,int st,int dr,int S,int D,pair<int,long long> val) {
    propag(nod,st,dr);

    if(D < st || S > dr) {
        return ;
    }

    if(S <= st && dr <= D) {
        aint[nod].first = 1LL * aint[nod].first * lgpow(val.first,dr - st + 1) % MOD;
        aint[nod].second = aint[nod].second | val.second;
        lazy[nod].first = 1LL * lazy[nod].first * val.first % MOD;
        lazy[nod].second = lazy[nod].second | val.second;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,S,D,val);
    update(nod * 2 + 1,mid + 1,dr,S,D,val);

    aint[nod].first = 1LL * aint[nod * 2].first * aint[2 * nod + 1].first % MOD;
    aint[nod].second = aint[nod * 2].second | aint[2 * nod + 1].second;
}

pair<int,long long> query(int nod,int st,int dr,int S,int D) {
    propag(nod,st,dr);

    if(D < st || S > dr) {
        return {1,0};
    }

    if(S <= st && dr <= D) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    pair<int,long long> a = query(nod * 2,st,mid,S,D);
    pair<int,long long> b = query(nod * 2 + 1,mid + 1,dr,S,D);

    a.first = 1LL * a.first * b.first % MOD;
    a.second = a.second | b.second;

    return a;
}

vector<int> primes;
vector<int> ch;
int n,q;

int main() {

    ciur[0] = ciur[1] = true;

    int sz = 0;

    for(int i = 2; i <= VMAX; i++) {
        if(ciur[i] == false) {
            for(int j = i; j <= VMAX; j += i) {
                mask[j] |= (1LL << sz);
                ciur[j] = true;
            }
            sz++;
            primes.push_back(i);
            ch.push_back(1LL * (i - 1) * lgpow(i,MOD - 2) % MOD);
        }
    }

    scanf("%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i].first);
        v[i].second = mask[v[i].first];
    }

    build(1,1,n);

    scanf("\n");

    while(q--) {
        scanf("%s",c);

        if(c[0] == 'T') {
            int l,r;
            scanf("%d %d\n",&l,&r);
            pair<int,long long> tmp = query(1,1,n,l,r);

            for(int i = 0; i < (int)primes.size(); i++) {
                if((tmp.second >> i) & 1) {
                    tmp.first = 1LL * tmp.first * ch[i] % MOD;
                }
            }

            printf("%d\n",tmp.first);
        }
        else {
            int l,r,x;
            scanf("%d %d %d\n",&l,&r,&x);
            update(1,1,n,l,r, {x,mask[x]});
        }
    }

    return 0;
}
