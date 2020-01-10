#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int inv100 = 828542813;
const int NMAX = 1e5;
int n;

bool banned[NMAX + 5][4];
int aint[4 * NMAX + 5][4];

int x[NMAX + 5];
int v[NMAX + 5];
int p[NMAX + 5];

void join(int nod,int l,int r,int lst_left) {
    memset(aint[nod],0,sizeof(aint[nod]));
    for(int m1 = 0; m1 < 4; m1++) {
        for(int m2 = 0; m2 < 4; m2++) {
            aint[nod][(m1 & 2) + (m2 & 1)] = (aint[nod][(m1 & 2) + (m2 & 1)] + (0LL + (banned[lst_left][(m1 & 1) * 2 + (m2 & 2) / 2] == false)) * aint[l][m1] * aint[r][m2]) % MOD;
        }
    }
}

void init(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod][0] = 1LL * p[st] * inv100 % MOD;
        aint[nod][3] = 1LL * (100 - p[st]) * inv100 % MOD;
        return ;
    }

    int mid = (st + dr) / 2;

    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);

    join(nod,nod * 2,nod * 2 + 1,mid);
}

void refresh(int nod,int st,int dr,int pos) {
    if(dr < pos || st > pos) {
        return ;
    }
    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    refresh(nod * 2,st,mid,pos);
    refresh(nod * 2 + 1,mid + 1,dr,pos);

    join(nod,nod * 2,nod * 2 + 1,mid);
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

struct frac_t {
    int a,b;

    frac_t(int a,int b) {
        this->a = a;
        this->b = b;
    }

    bool operator < (const frac_t &other)const {
        return 1LL * a * other.b < 1LL * b * other.a;
    }

    int to_mod() {
        return 1LL * a * lgpow(b,MOD - 2) % MOD;
    }
};

vector<pair<frac_t,pair<int,int> > > events;

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d",&x[i],&v[i],&p[i]);
        p[i] = 100 - p[i];
    }

    init(1,1,n);

    for(int i = 1; i < n; i++) {
        events.push_back({frac_t(x[i + 1] - x[i],v[i + 1] + v[i]),{i,2}});
        if(v[i + 1] > v[i]) {
            events.push_back({frac_t(x[i + 1] - x[i],v[i + 1] - v[i]),{i,0}});
        }
        else if(v[i] > v[i + 1]) {
            events.push_back({frac_t(x[i + 1] - x[i],v[i] - v[i + 1]),{i,3}});
        }
    }

    sort(events.begin(),events.end());

    int last_prob = 1;
    int ans = 0;

    for(auto it:events) {
        banned[it.second.first][it.second.second] = true;
        refresh(1,1,n,it.second.first);
        int prob = ((0LL + aint[1][0] + aint[1][1]) + (0LL + aint[1][2] + aint[1][3])) % MOD;
        int happen_prob = ((0LL + last_prob - prob) + MOD) % MOD;
        ans = (ans + 1LL * happen_prob * it.first.to_mod()) % MOD;
        last_prob = prob;
    }

    printf("%d\n",ans);

    return 0;
}
