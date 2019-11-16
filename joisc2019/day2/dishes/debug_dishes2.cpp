#include <cstdio>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int NMAX = 1e6;

int n,m;
int a[NMAX + 5];
int b[NMAX + 5];
int p[NMAX + 5];
int q[NMAX + 5];
long long s[NMAX + 5];
long long t[NMAX + 5];

int pref_lin[NMAX + 5];
int pref_col[NMAX + 5];

long long pref_sum_a[NMAX + 5];
long long pref_sum_b[NMAX + 5];

vector<int> event[NMAX + 5];

struct node_t {
    long long base_offset;
    long long sum;
    long long val;
    int lazy;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.base_offset = 0;
        ans.sum = (this->sum) + other.sum;
        ans.val = 0;
        ans.lazy = 0;
        return ans;
    }
} aint[4 * NMAX + 5];

void propag(int nod,int st,int dr) {
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    if(st == dr || aint[nod].lazy == 0) {
        return ;
    }

    aint[2 * nod].lazy |= aint[nod].lazy;
    aint[2 * nod + 1].lazy |= aint[nod].lazy;

    aint[2 * nod].val = aint[2 * nod].sum = 0;
    aint[2 * nod + 1].val = aint[2 * nod + 1].sum = 0;

    aint[nod].lazy = 0;
}

void build(int nod,int st,int dr) {
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    aint[nod].base_offset = 0;
    aint[nod].sum = 0;
    aint[nod].val = 0;
    aint[nod].lazy = 0;

    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
}

void update_val(int nod,int st,int dr,int pos,long long delta) { ///+= delta
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    assert(0 <= pos && pos <= n);
    propag(nod,st,dr);

    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].val += delta;
        aint[nod].sum = aint[nod].val;
        assert(st == 0 || aint[nod].val >= 0);
        return ;
    }

    int mid = (st + dr) / 2;

    update_val(nod * 2,st,mid,pos,delta);
    update_val(nod * 2 + 1,mid + 1,dr,pos,delta);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_offset(int nod,int st,int dr,int pos,int delta) { /// += delta_offset
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    assert(0 <= pos && pos <= n);
    propag(nod,st,dr);
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].base_offset += delta;
        aint[nod].sum = aint[nod].val;
        return ;
    }

    int mid = (st + dr) / 2;

    update_offset(nod * 2,st,mid,pos,delta);
    update_offset(nod * 2 + 1,mid + 1,dr,pos,delta);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_0(int nod,int st,int dr,int l,int r) {
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    assert(0 <= l && l <= r && r <= n);
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return ;
    }
    if(l <= st && dr <= r) {
        aint[nod].lazy = 1;
        aint[nod].sum = 0;
        aint[nod].val = 0;
        return ;
    }

    int mid = (st + dr) / 2;

    update_0(nod * 2,st,mid,l,r);
    update_0(nod * 2 + 1,mid + 1,dr,l,r);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}
long long query_sum(int nod,int st,int dr,int l,int r) {
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    assert(0 <= l && l <= r && r <= n);
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return 0;
    }

    if(l <= st && dr <= r) {
        return aint[nod].sum;
    }

    int mid = (st + dr) / 2;

    return query_sum(nod * 2,st,mid,l,r) + query_sum(nod * 2 + 1,mid + 1,dr,l,r);
}

long long get_val(int nod,int st,int dr,int pos) {
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    propag(nod,st,dr);
    if(dr < pos || st > pos) {
        return -1e18;
    }

    if(st == dr) {
        return aint[nod].val;
    }

    int mid = (st + dr) / 2;

    return max(get_val(nod * 2,st,mid,pos),get_val(nod * 2 + 1,mid + 1,dr,pos));
}

pair<long long,int> find_pos(int nod,int st,int dr,long long sum,int pos) {
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    assert(0 <= pos && pos <= n);
    propag(nod,st,dr);

    if(st == dr) {
        return {aint[nod].sum,st};
    }

    int mid = (st + dr) / 2;

    if(st <= pos && pos <= dr) {
        if(pos <= mid) {
            pair<long long,int> tmp = find_pos(nod * 2,st,mid,sum,pos);
            if(tmp.first < sum) {
                if(aint[nod * 2 + 1].sum + tmp.first >= sum) {
                    pair<long long,int> tmp_fiu = find_pos(nod * 2 + 1,mid + 1,dr,sum - tmp.first,pos);
                    tmp.first += tmp_fiu.first;
                    tmp.second = tmp_fiu.second;
                    return tmp;
                }
                else {
                    tmp.first += aint[nod * 2 + 1].sum;
                    tmp.second = dr;
                    return tmp;
                }
            }
            else {
                return tmp;
            }
        }
        else {
            pair<long long,int> tmp = find_pos(nod * 2 + 1,mid + 1,dr,sum,pos);
            return tmp;
        }
    }
    else {
        if(aint[nod * 2].sum >= sum) {
            pair<long long,int> tmp = find_pos(nod * 2,st,mid,sum,pos);
            return tmp;
        }
        else {
            pair<long long,int> tmp = find_pos(nod * 2 + 1,mid + 1,dr,sum - aint[nod * 2].sum,pos);
            tmp.first += aint[nod * 2].sum;
            return tmp;
        }
    }

}

int get_pos_sum(int pos,long long elem) {
    if(pos > n) {
        return n + 1;
    }

    pair<long long,int> tmp = find_pos(1,0,n,-elem,pos);

    if(tmp.first + elem < 0) {
        return n + 1;
    }

    assert(tmp.second >= pos);
    return tmp.second;
}

long long get_time(int i,int j) {
    return pref_sum_a[i] + pref_sum_b[j];
}

long long get_ans(int nod,int st,int dr) {
    assert(1 <= nod && nod <= 4 * n);
    assert(0 <= st && st <= dr && dr <= n);
    propag(nod,st,dr);
    if(st == dr) {
        return (aint[nod].val + aint[nod].base_offset);
    }

    int mid = (st + dr) / 2;

    return get_ans(nod * 2,st,mid) + get_ans(nod * 2 + 1,mid + 1,dr);
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;
    int sgn = 1;

    while(buff[ind] != '-' && ('0' > buff[ind] || '9' < buff[ind])) {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    if(buff[ind] == '-') {
        sgn = -1;
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while('0' <= buff[ind] && '9' >= buff[ind]) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans * sgn;
}

long long i64() {
    long long ans = 0;
    int sgn = 1;

    while(buff[ind] != '-' && ('0' > buff[ind] || '9' < buff[ind])) {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    if(buff[ind] == '-') {
        sgn = -1;
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while('0' <= buff[ind] && '9' >= buff[ind]) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans * sgn;
}

int main() {

    m = i32();
    n = i32();

    for(int i = 1; i <= m; i++) {
        b[i] = i32();
        t[i] = i64();
        q[i] = i32();
        pref_sum_b[i] = b[i] + pref_sum_b[i - 1];
    }

    for(int i = 1; i <= n; i++) {
        a[i] = i32();
        s[i] = i64();
        p[i] = i32();
        pref_sum_a[i] = a[i] + pref_sum_a[i - 1];
    }

    for(int j = 0; j <= m; j++) {
        int l = -1,r = n + 1;
        while(r - l > 1) {
            int mid = (l + r) / 2;
            if(get_time(mid,j) <= t[j]) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        pref_col[j] =  l;
    }


    for(int i = 0; i <= n; i++) {
        int l = -1,r = m + 1;

        while(r - l > 1) {
            int mid = (l + r) / 2;
            if(get_time(i,mid) <= s[i]) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        pref_lin[i] = l;
    }

    build(1,0,n);

    for(int i = 1; i <= n; i++) {
        if(pref_lin[i] > -1) {
            update_offset(1,0,n,i,p[i]);
            event[pref_lin[i] + 1].push_back(i);
        }
    }

    for(int j = 1; j <= m; j++) {
        for(auto it:event[j]) {
            if(p[it] < 0) {
                int k = get_pos_sum(it,p[it]);
                assert(k >= it);
                if(k <= n) {
                    assert(query_sum(1,0,n,it,k) + p[it] >= 0);
                    update_val(1,0,n,k,(query_sum(1,0,n,it,k) + p[it]) - get_val(1,0,n,k));
                }
                if(it <= k - 1) {
                    update_0(1,0,n,it,k - 1);
                }
                update_offset(1,0,n,it,-p[it]);
            }
            else {
                update_offset(1,0,n,it,-p[it]);
                update_val(1,0,n,it,+p[it]);
            }
        }
        if(pref_col[j] > -1) {
            update_val(1,0,n,0,q[j]);
            int k = get_pos_sum(pref_col[j] + 1,-q[j]);
            if(k <= n) {
                update_val(1,0,n,k,(query_sum(1,0,n,pref_col[j] + 1,k) - q[j]) - get_val(1,0,n,k));
            }
            if(pref_col[j] + 1 <= k - 1) {
                update_0(1,0,n,pref_col[j] + 1,k - 1);
            }
        }
    }

    printf("%lld\n",get_ans(1,0,n));

    return 0;
}
