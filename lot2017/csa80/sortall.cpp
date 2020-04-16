#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int NMAX = 5e4;
const int BUCK = 40;
const int MOD = 1e9 + 7;
const bool DEB = false;
const bool DEB2 = false;

int add(int a,int b) {
    a += b;

    if(a >= MOD) {
        a -= MOD;
    }

    return a;
}

int mult(int a,int b) {
    return 1LL * a * b % MOD;
}

struct node_t {
    int sum_x;
    int sum_y;
    int sum_xy;
    int cnt;
    int lazy_x;
    int lazy_y;

    node_t() {
    }

    node_t(int sum_x,int sum_y,int sum_xy,int cnt,int lazy_x,int lazy_y) {
        this->sum_x = sum_x;
        this->sum_y = sum_y;
        this->sum_xy = sum_xy;
        this->cnt = cnt;
        this->lazy_x = lazy_x;
        this->lazy_y = lazy_y;
    }

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.sum_x = add(this->sum_x,other.sum_x);
        ans.sum_y = add(this->sum_y,other.sum_y);
        ans.sum_xy = add(this->sum_xy,other.sum_xy);
        ans.cnt = add(this->cnt,other.cnt);
        ans.lazy_x = 0;
        ans.lazy_y = 0;
        return ans;
    }

    void propag(int lazy_x,int lazy_y) {
        this->lazy_x = add(this->lazy_x,lazy_x);
        this->lazy_y = add(this->lazy_y,lazy_y);
        this->sum_xy = add(add(this->sum_xy,mult(this->cnt,mult(lazy_x,lazy_y))),add(mult(this->sum_x,lazy_y),mult(this->sum_y,lazy_x)));
        this->sum_x = add(this->sum_x,mult(lazy_x,cnt));
        this->sum_y = add(this->sum_y,mult(lazy_y,cnt));
    }
};

node_t aint[4 * NMAX + 5];

void reset(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod] = node_t(0,1,0,1,0,0);
        return ;
    }

    int mid = (st + dr) / 2;

    reset(nod * 2,st,mid);
    reset(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void propag(int nod,int st,int dr) {
    if(st == dr || (aint[nod].lazy_x == 0 && aint[nod].lazy_y == 0)) {
        return ;
    }

    aint[nod * 2].propag(aint[nod].lazy_x,aint[nod].lazy_y);
    aint[nod * 2 + 1].propag(aint[nod].lazy_x,aint[nod].lazy_y);

    aint[nod].lazy_x = aint[nod].lazy_y = 0;
}

void update(int nod,int st,int dr,int l,int r,int dx,int dy) {
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return ;
    }

    if(l <= st && dr <= r) {
        aint[nod].propag(dx,dy);
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,dx,dy);
    update(nod * 2 + 1,mid + 1,dr,l,r,dx,dy);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

node_t query(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);

    if(r < st || l > dr) {
        return node_t(0,0,0,0,0,0);
    }

    if(l <= st && dr <= r) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
}

void afis(int nod,int st,int dr) {
//    propag(nod,st,dr);
    printf("%d %d %d : %d %d %d %d %d %d\n",nod,st,dr,aint[nod].sum_x,aint[nod].sum_y,aint[nod].sum_xy,aint[nod].cnt,aint[nod].lazy_x,aint[nod].lazy_y);
    if(st == dr) {
        return ;
    }
    int mid = (st + dr) / 2;
    afis(nod * 2,st,mid);
    afis(nod * 2 + 1,mid + 1,dr);
}

int n;
int v[NMAX + 5];
int lst_buck;
vector<int> positions[NMAX + 5];
int lst[NMAX + 5];
int bucket[NMAX + 5];
int l[NMAX + 5];
int r[NMAX + 5];

int process_with_outside(int l,int r) {
    reset(1,1,n);
    for(int i = 1; i <= n; i++) {
        lst[i] = 0;
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        if(v[i] > r) {
            if(DEB2)printf("on pos %d is too big,do nothing\n",i);
        }
        else if(v[i] >= l) {
            if(DEB2)printf("on pos %d val is in range, so i update the sum on %d %d with %d\n",i,lst[v[i]] + 1,i,v[i]);
            update(1,1,n,lst[v[i]] + 1,i,v[i],0);
        }
        else {
            if(DEB2)printf("on pos %d val is out of range, so i update the coef on %d %d with %d\n",i,lst[v[i]] + 1,i,1);
            update(1,1,n,lst[v[i]] + 1,i,0,1);
        }
        lst[v[i]] = i;
        ans = add(ans,query(1,1,n,1,n).sum_xy);
        if(DEB2)printf("overall sum of xy is %d\n",query(1,1,n,1,n).sum_xy);
    }

    return ans;
}

int aib[NMAX + 5];
int aib_cnt[NMAX + 5];

void update_aib(int pos,int val,int cnt) {
    if(DEB)printf("update on %d %d %d\n",pos,val,cnt);
    for(; pos <= n; pos += (-pos) & pos) {
        aib[pos] = add(aib[pos],val);
        aib_cnt[pos] += cnt;
    }
}

pair<int,int> query_aib(int pos) {
    if(DEB)    printf("query on %d ",pos);
    int ans = 0,cnt = 0;

    for(; pos; pos -= (-pos) & pos) {
        ans = add(ans,aib[pos]);
        cnt += aib_cnt[pos];
    }

    if(DEB)    printf("with answer %d %d\n",ans,cnt);
    return {ans,cnt};
}

int process_with_inside(int buck) {
    for(int i = l[buck]; i <= r[buck]; i++) {
        lst[i] = 0;
    }

    int ans = 0;

    for(int val = l[buck]; val <= r[buck]; val++) {
        for(int i = 0; i < (int)positions[buck].size() - 1; i++) {
            int it = positions[buck][i];
            if(v[it] < val) {
                if(lst[v[it]]) {
                    update_aib(lst[v[it]],MOD - lst[v[it]],-1);
                }
                update_aib(it,it,1);
            }
            lst[v[it]] = it;
            if(lst[val] == 0) {
                continue;
            }
            int cnt_between = query_aib(it).second - query_aib(lst[val]).second;
            int cnt = add(query_aib(lst[val]).first,mult(lst[val],cnt_between));
            if(DEB)            printf("coef of val %d on pos %d is %d deb stuff %d\n",val,it,cnt,cnt_between);
            ans = add(ans,mult(val,mult(cnt,positions[buck][i + 1] - positions[buck][i])));
        }
        for(auto it:positions[buck]) {
            if(lst[v[it]] == it) {
                if(v[it] < val) {
                    update_aib(lst[v[it]],MOD - lst[v[it]],-1);
                }
                lst[v[it]] = 0;
            }
        }
    }

    return ans;
}

int main() {

    freopen("sortall.in","r",stdin);
    freopen("sortall.out","w",stdout);

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    int lst_buck = 0;

    for(int st = 1; st <= n; st += BUCK) {
        int dr = min(n,st + BUCK - 1);
        lst_buck++;
        l[lst_buck] = st;
        r[lst_buck] = dr;
        for(int i = st; i <= dr; i++) {
            bucket[i] = lst_buck;
        }
    }

    for(int i = 1; i <= n; i++) {
        positions[bucket[v[i]]].push_back(i);
    }

    for(int i = 1; i <= lst_buck; i++) {
        positions[i].push_back(n + 1);
    }

    if(DEB2) {
        process_with_outside(5,5);
        return 0;
    }

    int ans = 0;

    for(int i = 1; i <= lst_buck; i++) {
        ans = add(ans,add(process_with_outside(l[i],r[i]),process_with_inside(i)));
    }

    for(int i = 1; i <= n && DEB2; i++) {
        printf("deb %d %d\n",i,process_with_outside(l[i],r[i]));
    }

    printf("%d\n",ans);

    return 0;
}
