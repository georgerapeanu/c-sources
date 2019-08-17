#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("picazo.in","r");
FILE *g = fopen("picazo.out","w");

const int NMAX = 1e5;

int n,k,q;
int l[NMAX + 5];
int r[NMAX + 5];

long long dp[NMAX + 5];

vector<int> in[NMAX + 5];
vector<int> out[NMAX + 5];

int smen[NMAX + 5];
long long sum[NMAX + 5];

long long aint[4 * NMAX + 5];
long long lazy[4 * NMAX + 5];

void propag(int nod,int st,int dr) {

    if(st == dr || lazy[nod] == 0) {
        return ;
    }

    aint[2 * nod] += lazy[nod];
    lazy[2 * nod] += lazy[nod];
    aint[2 * nod + 1] += lazy[nod];
    lazy[2 * nod + 1] += lazy[nod];

    lazy[nod] = 0;
}

void update(int nod,int st,int dr,int l,int r,long long val) {

    propag(nod,st,dr);

    if(r < st || l > dr) {
        return ;
    }

    if(l <= st && dr <= r) {
        aint[nod] += val;
        lazy[nod] += val;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,val);
    update(nod * 2 + 1,mid + 1,dr,l,r,val);

    aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
}

long long query(int nod,int st,int dr,int l,int r) {

    propag(nod,st,dr);

    if(r < st || l > dr) {
        return 0;
    }

    if(l <= st && dr <= r) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return max(query(nod * 2,st,mid,l,r),query(nod * 2 + 1,mid + 1,dr,l,r));
}

int main() {

    fscanf(f,"%d %d %d",&n,&k,&q);

    for(int i = 1; i <= q; i++) {
        fscanf(f,"%d %d",&l[i],&r[i]);
        in[l[i]].push_back(i);
        out[r[i]].push_back(i);
        smen[l[i]]++;
        smen[r[i] + 1]--;
    }

    for(int i = 1; i <= n; i++) {
        smen[i] += smen[i - 1];
        sum[i] = smen[i] + sum[i - 1];
    }

    update(1,0,n,0,0,k);
    for(int i = 1; i <= n + 1; i++) {
        update(1,0,n,0,i - 1,(int)in[i].size());

        dp[i] = query(1,0,n,0,i) + sum[i - 1] - 1LL * k * i;

        for(auto it:out[i]) {
            update(1,0,n,0,l[it] - 1,-1);
        }

        update(1,0,n,i,i,dp[i] - sum[i] + 1LL * k * (i + 1));
    }

    fprintf(g,"%lld\n",dp[n + 1]);

    fclose(f);
    fclose(g);

    return 0;
}
