#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int NMAX = 1e5;
const int EXPMAX = 1e5;
const int LGMAX = 17;
const int AINTMAX = LGMAX + EXPMAX;

const int BASE = 31;
const int MOD1 = 666013;
const int MOD2 = 1e9 + 7;
const int MOD = 1e9 + 7;

int pw1[AINTMAX + 5];
int pw2[AINTMAX + 5];

void init_hsh() {
    pw1[0] = pw2[0] = 1;
    for(int i = 1; i <= AINTMAX; i++) {
        pw1[i] = 1LL * BASE * pw1[i - 1] % MOD1;
        pw2[i] = 1LL * BASE * pw2[i - 1] % MOD2;
    }
}

struct hsh_t {
    int len;
    int h1;
    int h2;

    hsh_t() {
        this->len=0;
        this->h1=0;
        this->h2=0;
    }

    hsh_t(int len,int val) {
        this->len = len;
        for(int i = 1; i <= len; i++) {
            this->h1 = (1LL * this->h1 * BASE + val) % MOD1;
            this->h2 = (1LL * this->h2 * BASE + val) % MOD2;
        }
    }

    hsh_t(int len,int h1,int h2) {
        this->len = len;
        this->h1 = h1;
        this->h2 = h2;
    }

    hsh_t operator + (const hsh_t &other)const {
        hsh_t ans;
        ans.len = this->len + other.len;
        ans.h1 = (1LL * this->h1 * pw1[other.len] + other.h1) % MOD1;
        ans.h2 = (1LL * this->h2 * pw2[other.len] + other.h2) % MOD2;
        return ans;
    }

    bool operator == (const hsh_t &other)const {
        return this->len == other.len && this->h1 == other.h1 && this->h2 == other.h2;
    }

    bool operator != (const hsh_t &other)const {
        return this->len != other.len || this->h1 != other.h1 || this->h2 != other.h2;
    }

};

struct node_t {
    bool lazy;
    int sum;
    hsh_t hsh;

    node_t() {
        this->lazy = false;
        this->sum = 0;
        this->hsh = hsh_t();
    }

    node_t(bool lazy,int sum,hsh_t hsh) {
        this->lazy = lazy;
        this->sum = sum;
        this->hsh = hsh;
    }

    node_t operator + (const node_t &other) {
        node_t ans;
        ans.sum = this->sum + other.sum;
        ans.lazy = false;
        ans.hsh = this->hsh + other.hsh;
        return ans;
    }

    bool operator == (const node_t &other)const {
        return this->lazy == other.lazy && this->sum == other.sum && this->hsh == other.hsh;
    }

    bool operator != (const node_t &other)const {
        return this->lazy != other.lazy || this->sum != other.sum || this->hsh != other.hsh;
    }
};

class PersistenSegmentTree {
private:
    int n;
    vector<int> leftson;
    vector<int> rightson;
    vector<node_t> data;

    void propag(int nod,int st,int dr) {
        if(st == dr || data[nod].lazy == false) {
            data[nod].lazy = false;
            return ;
        }

        int nl,nr;

        leftson.push_back(leftson[leftson[nod]]);
        rightson.push_back(rightson[leftson[nod]]);
        data.push_back(data[leftson[nod]]);
        nl = (int)leftson.size() - 1;

        leftson.push_back(leftson[rightson[nod]]);
        rightson.push_back(rightson[rightson[nod]]);
        data.push_back(data[rightson[nod]]);
        nr = (int)leftson.size() - 1;

        leftson[nod] = nl;
        rightson[nod] = nr;

        int mid = (st + dr) / 2;

        data[nl] = node_t(true,0,hsh_t(mid - st + 1,0,0));
        data[nr] = node_t(true,0,hsh_t(dr - mid,0,0));

        data[nod] = data[nl] + data[nr];

        data[nod].lazy = false;
    }

    int build(int st,int dr) {
        data.push_back(node_t(false,0,hsh_t(dr - st + 1,0,0)));
        leftson.push_back(0);
        rightson.push_back(0);

        int id = leftson.size() - 1;

        if(st == dr) {
            return id;
        }

        int mid = (st + dr) / 2;

        int ls = build(st,mid);
        int rs = build(mid + 1,dr);

        leftson[id] = ls;
        rightson[id] = rs;

        data[id] = data[ls] + data[rs];

        return id;
    }

    int update_range(int nod,int st,int dr,int S,int D) {
        propag(nod,st,dr);
        if(dr < S || st > D) {
            return nod;
        }

        if(S <= st && dr <= D) {
            leftson.push_back(leftson[nod]);
            rightson.push_back(rightson[nod]);
            data.push_back(node_t(true,0,hsh_t(dr - st + 1,0,0)));
            return (int)data.size() - 1;
        }

        int mid = (st + dr) / 2;

        int ls = update_range(leftson[nod],st,mid,S,D);
        int rs = update_range(rightson[nod],mid + 1,dr,S,D);

        leftson.push_back(ls);
        rightson.push_back(rs);
        data.push_back(data[ls] + data[rs]);

        return (int)data.size() - 1;
    }

    int update_single(int nod,int st,int dr,int pos) {
        propag(nod,st,dr);
        if(dr < pos || st > pos) {
            return nod;
        }

        if(st == dr) {
            leftson.push_back(leftson[nod]);
            rightson.push_back(rightson[nod]);
            data.push_back(node_t(false,1,hsh_t(1,1,1)));
            return (int)data.size() - 1;
        }

        int mid = (st + dr) / 2;

        int ls = update_single(leftson[nod],st,mid,pos);
        int rs = update_single(rightson[nod],mid + 1,dr,pos);

        leftson.push_back(ls);
        rightson.push_back(rs);
        data.push_back(data[ls] + data[rs]);

        return (int)data.size() - 1;
    }

    int first_0(int nod,int st,int dr,int pos) {
        propag(nod,st,dr);
        if(st == dr) {
            if(data[nod].sum == 0) {
                return dr;
            }
            else {
                return dr + 1;
            }
        }

        int mid = (st + dr) / 2;
        int ans = 0;
        if(pos <= mid) {
            ans = first_0(leftson[nod],st,mid,pos);
            if(ans < mid + 1) {
                return ans;
            }
            if(data[rightson[nod]].sum == dr - mid) {
                ans = dr + 1;
                return ans;
            }
            return first_0(rightson[nod],mid + 1,dr,pos);
        }
        else {
            return first_0(rightson[nod],mid + 1,dr,pos);
        }
    }

public:
    PersistenSegmentTree(int n) {
        this->n = n;
        this->leftson = vector<int>(1,0);
        this->rightson = vector<int>(1,0);
        this->data = vector<node_t>(1,node_t());
        build(1,n);
    }

    bool cmp(int a,int b) {
        int st = 1,dr = n;
        propag(a,st,dr);
        propag(b,st,dr);

        if(data[a].hsh == data[b].hsh) {
            return a < b;
        }

        while(st < dr) {
            propag(a,st,dr);
            propag(b,st,dr);

            if(data[rightson[a]].hsh == data[rightson[b]].hsh) {
                a = leftson[a];
                b = leftson[b];
                dr = (st + dr) / 2;
            }
            else {
                a = rightson[a];
                b = rightson[b];
                st = (st + dr) / 2 + 1;
            }
        }

        return data[a].sum < data[b].sum;
    }

    int add(int nod,int pos) {
        int rgt = first_0(nod,1,n,pos);
        nod = update_range(nod,1,n,pos,rgt - 1);
        nod = update_single(nod,1,n,rgt);
        return nod;
    }

    void toModularInt(int nod,int &ans,int st = -1,int dr = -1) {
        if(st == -1) {
            st = 1;
            dr = n;
        }
        propag(nod,st,dr);

        if(st == dr) {
            ans = (ans * 2 + data[nod].sum) % MOD;
            return ;
        }

        int mid = (st + dr) / 2;

        toModularInt(rightson[nod],ans,mid + 1,dr);
        toModularInt(leftson[nod],ans,st,mid);
    }


    int sz() {
        return (int)leftson.size() - 1;
    }
} T(AINTMAX + 5);

int n,m,s,t;
vector<pair<int,int> > graph[NMAX + 5];

int best[NMAX + 5];
int ant[NMAX + 5];

struct smenuri_t {
    int nod;
    int root;

    bool operator < (const smenuri_t &other)const {
        return T.cmp(other.root,root);
    }
};

priority_queue<smenuri_t> pq;

int main() {
    init_hsh();

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int u,v,x;
        scanf("%d %d %d",&u,&v,&x);
        x++;
        graph[u].push_back({v,x});
        graph[v].push_back({u,x});
    }

    scanf("%d %d",&s,&t);

    pq.push({s,1});
    best[s] = 1;

    while(!pq.empty()) {
        int nod = pq.top().nod;
        int root = pq.top().root;

        pq.pop();

        if(best[nod] != root) {
            continue;
        }

        if(nod == t) {
            break;
        }

        for(auto it:graph[nod]) {
            int n_root = T.add(root,it.second);
            if(best[it.first] == 0 || T.cmp(n_root,best[it.first])) {
                best[it.first] = n_root;
                pq.push({it.first,n_root});
                ant[it.first] = nod;
            }
        }
    }

    int ans = 0;

    if(best[t] != 0) {
        T.toModularInt(best[t],ans);
        printf("%d\n",ans);
        vector<int> path;

        while(t) {
            path.push_back(t);
            t = ant[t];
        }

        reverse(path.begin(),path.end());

        printf("%d\n",(int)path.size());

        for(auto it:path) {
            printf("%d ",it);
        }
    }
    else {
        ans = -1;
        printf("%d\n",ans);
    }

    return 0;
}

