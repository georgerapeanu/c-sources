#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
pair<int,int> v[NMAX + 5];

int aint[4 * NMAX + 5];
int lazy[4 * NMAX + 5];

long long ans;

void propag(int nod,int st,int dr) {
    if(lazy[nod] == 0 || st == dr) {
        return ;
    }
    aint[2 * nod] += lazy[nod];
    lazy[2 * nod] += lazy[nod];
    aint[2 * nod + 1] += lazy[nod];
    lazy[2 * nod + 1] += lazy[nod];
    lazy[nod] = 0;
}

void dfs(int nod,int st,int dr) {
    propag(nod,st,dr);
    if(st == dr) {
        ans += 1LL * (aint[nod] - 1) * (aint[nod]) / 2;
        return ;
    }

    dfs(nod * 2,st,(st + dr) / 2);
    dfs(nod * 2 + 1,(st + dr) / 2 + 1,dr);
}

void update(int nod,int st,int dr,int l,int r,int val) {
    propag(nod,st,dr);

    if(l <= st && dr <= r) {
        lazy[nod] += val;
        aint[nod] += val;
        return ;
    }

    if(r < st || l > dr) {
        return ;
    }

    update(nod * 2,st,(st + dr) / 2,l,r,val);
    update(nod * 2 + 1,(st + dr) / 2 + 1,dr,l,r,val);

    aint[nod] = min(aint[2 * nod],aint[2 * nod + 1]);
}

int find_pos(int nod,int st,int dr,int val) { ///leftmost pos with value <= val
    propag(nod,st,dr);
    if(st == dr) {
        return st;
    }
    if(aint[2 * nod] <= val) {
        return find_pos(2 * nod,st,(st + dr) / 2,val);
    }
    else {
        return find_pos(2 * nod + 1,(st + dr) / 2 + 1,dr,val);
    }
}

int get_val(int nod,int st,int dr,int pos) {
    propag(nod,st,dr);
    if(st == dr) {
        return aint[nod];
    }
    if(pos <= (st + dr) / 2) {
        return get_val(nod * 2,st,(st + dr) / 2,pos);
    }
    else {
        return get_val(nod * 2 + 1,(st + dr) / 2 + 1,dr,pos);
    }
}


int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&v[i].first,&v[i].second);
    }

    sort(v + 1,v + 1 + n);

    for(int i = 1; i <= n; i++) {
        if(v[i].second == 0) {
            continue;
        }
        int tmp = get_val(1,1,NMAX,v[i].first - v[i].second + 1);
        int l1 = find_pos(1,1,NMAX,tmp);
        int l2 = (tmp == 0 || tmp < get_val(1,1,NMAX,v[i].first)? v[i].first + 1:find_pos(1,1,NMAX,tmp - 1));

        if(v[i].first - l2 + 1 > 0) {
            update(1,1,NMAX,l2,v[i].first,1);
            v[i].second -= (v[i].first - l2 + 1);
        }
        if(v[i].second > 0) {
            update(1,1,NMAX,l1,l1 + v[i].second - 1,1);
        }
    }

    dfs(1,1,NMAX);

    printf("%lld\n",ans);

    return 0;
}
