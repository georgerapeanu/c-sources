#include <cstdio>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <unordered_map>
#include <cstring>

using namespace std;

const int NMAX = 50000;

const int BASE = 50021;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

int pw1[NMAX + 5];
int pw2[NMAX + 5];

struct hsh_t {
    int h1;
    int h2;
    int len;

    hsh_t() {
        this->h1 = 0;
        this->h2 = 0;
        this->len = 0;
    }

    hsh_t(const int &val) {
        this->h1 = val;
        this->h2 = val;
        this->len = 1;
    }

    hsh_t operator + (const hsh_t &other)const {
        hsh_t ans;
        ans.h1 = (1LL * this->h1 * pw1[other.len] + other.h1) % MOD1;
        ans.h2 = (1LL * this->h2 * pw2[other.len] + other.h2) % MOD2;
        ans.len = this->len + other.len;
        return ans;
    }

    bool operator < (const hsh_t &other)const {
        if(this->h1 != other.h1) {
            return this->h1 < other.h1;
        }
        if(this->h2 != other.h2) {
            return this->h2 < other.h2;
        }
        return this->len < other.len;
    }

    long long to_ll() {
        return ((long long)MOD2) * h1 + h2;
    }
};

struct node_t {
    node_t *l;
    node_t *r;

    int prio;
    pair<int,int> key;
    int value;
    hsh_t hsh;

    node_t(node_t *l,node_t *r,const int &prio,const pair<int,int> &key,const int &value,const hsh_t &hsh) {
        this->l = l;
        this->r = r;
        this->prio = prio;
        this->key = key;
        this->hsh = hsh;
        this->value = value;
    }

    void refresh() {
        if(this->prio >= 0) { /// is not nill
            this->hsh = this->l->hsh + hsh_t(value) + this->r->hsh;
        }
    }

}*nill,*root;

node_t* join(node_t *&r1,node_t *&r2) {
    if(r1 == nill) {
        return r2;
    }
    if(r2 == nill) {
        return r1;
    }
    if(r1->prio > r2->prio) {
        node_t* tmp = join(r1->r,r2);
        r1->r = tmp;
        r1->refresh();
        return r1;
    }
    else {
        node_t* tmp = join(r1,r2->l);
        r2->l = tmp;
        r2->refresh();
        return r2;
    }
}

pair<node_t*,node_t*> split(node_t *&root,const pair<int,int> &key) {
    if(root == nill) {
        return {nill,nill};
    }

    if(root->key <= key) {
        pair<node_t*,node_t*> tmp = split(root->r,key);
        root->r = tmp.first;
        root->refresh();
        tmp.first = root;
        return tmp;
    }
    else {
        pair<node_t*,node_t*> tmp = split(root->l,key);
        root->l = tmp.second;
        root->refresh();
        tmp.second = root;
        return tmp;
    }
}

node_t* ins(node_t *&root,node_t *node) {
    pair<node_t*,node_t*> tmp = split(root,node->key);
    root = join(tmp.first,node);
    root = join(root,tmp.second);
    return root;
}

node_t* rem(node_t *&root,const pair<int,int> &key) {
    pair<node_t*,node_t*> tmp = split(root,key);
    pair<node_t*,node_t*> tmp2 = split(tmp.first, {key.first,key.second - 1});
    tmp2.first = join(tmp2.first,tmp.second);
    return tmp2.first;
}

FILE *f = fopen("clasament2.in","r");
FILE *g = fopen("clasament2.out","w");

int n,m;
pair<int,int> key[NMAX + 5];

mt19937 gen;

int my_rand() {
    return gen() & ((1LL << 31) - 1);
}

int main() {

    gen = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    pw1[0] = 1;
    pw2[0] = 1;

    for(int i = 1; i <= NMAX; i++) {
        pw1[i] = 1LL * BASE * pw1[i - 1] % MOD1;
        pw2[i] = 1LL * BASE * pw2[i - 1] % MOD2;
    }

    nill = new node_t(NULL,NULL,-1, {0,0},0,hsh_t());
    root = nill;

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        int val;
        fscanf(f,"%d",&val);
        root = ins(root,new node_t(nill,nill,my_rand(),key[i] = {-val,0},i,hsh_t(i)));
    }

    unordered_map<long long,int> fr;

    fr[root->hsh.to_ll()] = 1;

    for(int i = 1; i <= m; i++) {
        int pos,val;
        fscanf(f,"%d %d",&pos,&val);
        root = rem(root,key[pos]);
        root = ins(root,new node_t(nill,nill,my_rand(),key[pos] = {-val,i},pos,hsh_t(pos)));
        fprintf(g,"%d\n",fr[root->hsh.to_ll()]);
        fr[root->hsh.to_ll()]++;
    }

    fclose(f);
    fclose(g);

    return 0;
}
