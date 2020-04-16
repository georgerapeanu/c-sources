#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

struct node_t {
    int min_val;
    int pos;
    int cnt;

    node_t operator + (const node_t &other)const {
        node_t ans;
        if(this->min_val < other.min_val) {
            ans.min_val = this->min_val;
            ans.pos = this->pos;
        }
        else {
            ans.min_val = other.min_val;
            ans.pos = other.pos;
        }

        ans.cnt = this->cnt + other.cnt;

        return ans;
    }
};

node_t aint[4 * NMAX + 5];

int n;

int p[NMAX + 5];
int q[NMAX + 5];

void build(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod] = {p[st],st,1};
        return ;
    }
    int mid = (st + dr) / 2;
    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int pos,int val,int cnt) {
    if(dr < pos || st > pos) {
        return;
    }
    if(st == dr) {
        aint[nod] = {val,st,cnt};
        return ;
    }
    int mid = (st + dr) / 2;
    update(nod * 2,st,mid,pos,val,cnt);
    update(nod * 2 + 1,mid + 1,dr,pos,val,cnt);
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

node_t query(int nod,int st,int dr,int l,int r) {
    if(r < st || l > dr) {
        return {(int)1e9,0,0};
    }
    if(l <= st && dr <= r) {
        return aint[nod];
    }
    int mid = (st + dr) / 2;
    return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
}

int aib[NMAX + 5];

void update_aib(int pos,int val) {
    for(; pos <= n; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int query_aib(int pos) {
    int ans = 0;
    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }
    return ans;
}

int find_kth(int nod,int st,int dr,int pos) {
    if(st == dr) {
        return st;
    }
    int mid = (st + dr) / 2;
    if(aint[nod * 2].cnt < pos) {
        return find_kth(nod * 2 + 1,mid + 1,dr,pos - aint[nod * 2].cnt);
    }
    else {
        return find_kth(nod * 2,st,mid,pos);
    }
}

int gl_ans[NMAX + 5];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&p[i]);
    }

    build(1,1,n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&q[i]);
        update_aib(q[i],1);
    }

    int ans = 0;

    for(int i = n; i; i--) {
        int pos_q = query_aib(q[i]);
        int pos = find_kth(1,1,n,pos_q);
        ans = max(ans,query(1,1,n,pos,n).min_val);
        update_aib(q[i],-1);
        update(1,1,n,query(1,1,n,pos,n).pos,1e9,0);
        gl_ans[i] = ans;
    }

    for(int i = 1; i <= n; i++) {
        printf("%d ",gl_ans[i]);
    }

    return 0;
}
