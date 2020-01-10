#include <bits/stdc++.h>

using namespace std;

const int NMAX = 6e5;
const int MASK = (1 << 30) - 1;
const int inf = 1 << 30;

int n;
int fail[NMAX + 5];

char s[NMAX + 5];
int w[NMAX + 5];
int link[NMAX + 5];

struct node_t {
    int lazy;
    long long sum;
    int max_val;
    int min_val;
    int active;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.lazy = -1;
        ans.sum = this->sum + other.sum;
        ans.max_val = max(this->max_val,other.max_val);
        ans.min_val = min(this->min_val,other.min_val);
        ans.active = this->active + other.active;
        return ans;
    }

} aint[4 * NMAX + 5];

void propag(int nod,int st,int dr) {
    if(st == dr || aint[nod].lazy == -1) {
        return;
    }

    aint[nod * 2].lazy = aint[nod].lazy;
    aint[nod * 2].sum = 1LL * aint[nod * 2].active * aint[nod].lazy;
    if(aint[nod * 2].active > 0) {
        aint[nod * 2].max_val = aint[nod].lazy;
        aint[nod * 2].min_val = aint[nod].lazy;
    }
    else {
        aint[nod * 2].max_val = -inf;
        aint[nod * 2].min_val = inf;
    }

    aint[nod * 2 + 1].lazy = aint[nod].lazy;
    aint[nod * 2 + 1].sum = 1LL * aint[nod * 2 + 1].active * aint[nod].lazy;
    if(aint[nod * 2 + 1].active > 0) {
        aint[nod * 2 + 1].max_val = aint[nod].lazy;
        aint[nod * 2 + 1].min_val = aint[nod].lazy;
    }
    else {
        aint[nod * 2 + 1].max_val = -inf;
        aint[nod * 2 + 1].min_val = inf;
    }

    aint[nod].lazy = -1;
}

void init(int nod,int st,int dr) {
    if(st == dr) {
        aint[nod].max_val = -inf;
        aint[nod].min_val = inf;
        aint[nod].sum = 0;
        aint[nod].lazy = -1;
        aint[nod].active = 0;
        return ;
    }

    int mid = (st + dr) / 2;

    init(nod * 2,st,mid);
    init(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int pos,int val) {
    propag(nod,st,dr);

    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        if(val < 0) {
            aint[nod].max_val = -inf;
            aint[nod].min_val = inf;
            aint[nod].sum = 0;
            aint[nod].lazy = -1;
            aint[nod].active = 0;
        }
        else {
            aint[nod].max_val = val;
            aint[nod].min_val = val;
            aint[nod].lazy = -1;
            aint[nod].sum = val;
            aint[nod].active = 1;
        }
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int l,int r,int val) {
    propag(nod,st,dr);

    if(r < st || l > dr || aint[nod].max_val <= val) {
        return ;
    }

    if(l <= st && dr <= r && aint[nod].min_val >= val) {
        aint[nod].lazy = val;
        aint[nod].sum = 1LL * aint[nod].active * val;
        if(aint[nod].active > 0) {
            aint[nod].max_val = aint[nod].min_val = val;
        }
        else {
            aint[nod].max_val = -inf;
            aint[nod].min_val = inf;
        }
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,l,r,val);
    update(nod * 2 + 1,mid + 1,dr,l,r,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

node_t query(int nod,int st,int dr,int l,int r) {
    propag(nod,st,dr);

    if(dr < l || st > r) {
        node_t neutru;
        neutru.lazy = -1;
        neutru.max_val = -inf;
        neutru.min_val = inf;
        neutru.sum = 0;
        neutru.active = 0;
        return neutru;
    }

    if(l <= st && dr <= r) {
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
}

void erase_suff(int pos) {
    update(1,1,n,pos,-1);
}

void insert_suff(int pos) {
    update(1,1,n,pos,inf);
}

void add_to_all(int val) {
    update(1,1,n,1,n,val);
}

long long sum_all() {
    return query(1,1,n,1,n).sum;
}

const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

char getc() {
    while(buff[ind] > 'z' || buff[ind] < 'a') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    char ans = buff[ind];

    if(++ind >= LEN) {
        ind = 0;
        fread(buff,1,LEN,stdin);
    }

    return ans;
}

int i32() {
    while(buff[ind] > '9' || buff[ind] < '0') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    int ans = 0;
    while(buff[ind] <= '9' && buff[ind] >= '0') {
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans;
}

class Bignum {
public:
    vector<int> cf;

    Bignum() {
        cf = {0};
    }

    Bignum operator + (const long long &other)const {

        Bignum ans;
        ans.cf.clear();

        long long t = other;

        for(int i = 0; i < (int)cf.size() || t; i++) {
            ans.cf.push_back((i < (int)cf.size() ? cf[i]:0) + (t % 10));
            t /= 10;
            t += ans.cf.back() / 10;
            ans.cf.back() %= 10;
        }

        return ans;
    }

    void afis() {
        for(int i = (int)cf.size() - 1; i >= 0; i--) {
            printf("%d",cf[i]);
        }
        printf("\n");
    }
};

int main() {

    n = i32();

    init(1,1,n);

    Bignum ans;

    int lst_ans = 0;
    int mod_ans = 0;

    for(int i = 1; i <= n; i++) {
        char c;
        int val;

        c = getc();
        val = i32();

        s[i] = ((c - 'a' + mod_ans) % ('z' - 'a' + 1)) + 'a';
        w[i] = val ^ lst_ans;
        if(i > 1) {
            int k = fail[i - 1];
            while(k && s[k + 1] != s[i]) {
                k = fail[k];
            }
            if(s[k + 1] == s[i]) {
                k++;
            }
            fail[i] = k;
            link[i - 1] = (s[i] == s[fail[i - 1] + 1] ? link[fail[i - 1]]:fail[i - 1]);
            int nod = i - 1;
            while(nod) {
                if(s[nod + 1] == s[i]) {
                    nod = link[nod];
                }
                else {
                    erase_suff((i - 1) - nod + 1);
                    nod = fail[nod];
                }
            }
        }
        if(s[i] == s[1]) {
            insert_suff(i);
        }
        add_to_all(w[i]);
        ans = ans + sum_all();
        lst_ans = ((0LL + lst_ans) + sum_all()) & MASK;
        mod_ans = ((0LL + mod_ans) + sum_all()) % ('z' - 'a' + 1);

        ans.afis();
    }

    return 0;
}
