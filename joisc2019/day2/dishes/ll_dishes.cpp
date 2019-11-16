#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e6;

long long n,m;
long long a[NMAX + 5];
long long b[NMAX + 5];
long long p[NMAX + 5];
long long q[NMAX + 5];
long long s[NMAX + 5];
long long t[NMAX + 5];

long long pref_lin[NMAX + 5];
long long pref_col[NMAX + 5];

long long pref_sum_a[NMAX + 5];
long long pref_sum_b[NMAX + 5];

vector<long long> event[NMAX + 5];

struct node_t {
    long long base_offset;
    long long sum;
    long long val;
    long long lazy;

    node_t operator + (const node_t &other)const {
        node_t ans;
        ans.base_offset = 0;
        ans.sum = (this->sum) + other.sum;
        ans.val = 0;
        ans.lazy = 0;
        return ans;
    }
} aint[4 * NMAX + 5];

void propag(long long nod,long long st,long long dr) {
    if(st == dr || aint[nod].lazy == 0) {
        return ;
    }

    aint[2 * nod].lazy |= aint[nod].lazy;
    aint[2 * nod + 1].lazy |= aint[nod].lazy;

    aint[2 * nod].val = aint[2 * nod].sum = 0;
    aint[2 * nod + 1].val = aint[2 * nod + 1].sum = 0;

    aint[nod].lazy = 0;
}

void build(long long nod,long long st,long long dr) {
    aint[nod].base_offset = 0;
    aint[nod].sum = 0;
    aint[nod].val = 0;
    aint[nod].lazy = 0;

    if(st == dr) {
        return ;
    }

    long long mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
}

void update_val(long long nod,long long st,long long dr,long long pos,long long delta) { ///+= delta
    propag(nod,st,dr);

    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].val += delta;
        if(st != 0)aint[nod].val = max(0LL,aint[nod].val);
        aint[nod].sum = aint[nod].val;
        return ;
    }

    long long mid = (st + dr) / 2;

    update_val(nod * 2,st,mid,pos,delta);
    update_val(nod * 2 + 1,mid + 1,dr,pos,delta);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_offset(long long nod,long long st,long long dr,long long pos,long long delta,bool initial = false) { /// += delta_offset
    propag(nod,st,dr);
    if(dr < pos || st > pos) {
        return ;
    }

    if(st == dr) {
        aint[nod].base_offset += delta;
        if(initial == false) {
            aint[nod].val -= delta;
            aint[nod].val = max(aint[nod].val,0LL);
        }
        aint[nod].sum = aint[nod].val;
        return ;
    }

    long long mid = (st + dr) / 2;

    update_offset(nod * 2,st,mid,pos,delta,initial);
    update_offset(nod * 2 + 1,mid + 1,dr,pos,delta,initial);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update_0(long long nod,long long st,long long dr,long long l,long long r) {
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

    long long mid = (st + dr) / 2;

    update_0(nod * 2,st,mid,l,r);
    update_0(nod * 2 + 1,mid + 1,dr,l,r);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}
long long query_sum(long long nod,long long st,long long dr,long long l,long long r) {
    propag(nod,st,dr);
    if(r < st || l > dr) {
        return 0;
    }

    if(l <= st && dr <= r) {
        return aint[nod].sum;
    }

    long long mid = (st + dr) / 2;

    return query_sum(nod * 2,st,mid,l,r) + query_sum(nod * 2 + 1,mid + 1,dr,l,r);
}

long long get_val(long long nod,long long st,long long dr,long long pos) {
    propag(nod,st,dr);
    if(dr < pos || st > pos) {
        return -1;
    }

    if(st == dr) {
        return aint[nod].val;
    }

    long long mid = (st + dr) / 2;

    return max(get_val(nod * 2,st,mid,pos),get_val(nod * 2 + 1,mid + 1,dr,pos));
}

pair<long long,long long> find_pos(long long nod,long long st,long long dr,long long sum,long long pos) {
    propag(nod,st,dr);

    if(st == dr) {
        return {aint[nod].sum,st};
    }

    long long mid = (st + dr) / 2;

    if(st <= pos && dr <= pos) {
        if(pos <= mid) {
            pair<long long,long long> tmp = find_pos(nod * 2,st,mid,sum,pos);
            if(tmp.first < sum) {
                if(aint[nod * 2 + 1].sum + tmp.first >= sum) {
                    pair<long long,long long> tmp_fiu = find_pos(nod * 2 + 1,mid + 1,dr,sum - tmp.first,pos);
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
        }
        else {
            return find_pos(nod * 2 + 1,mid + 1,dr,sum,pos);
        }
    }
    else {
        if(aint[nod * 2].sum >= sum) {
            return find_pos(nod * 2,st,mid,sum,pos);
        }
        else {
            pair<long long,long long> tmp = find_pos(nod * 2 + 1,mid + 1,dr,sum - aint[nod * 2].sum,pos);
            tmp.first += aint[nod * 2].sum;
            return tmp;
        }
    }

}

long long get_pos_sum(long long pos,long long elem) {

    long long base_sum = query_sum(1,0,n,0,pos - 1) - elem;

    if(aint[1].sum < base_sum) {
        return n + 1;
    }

    long long tmp = find_pos(1,0,n,base_sum,pos).second;
    return tmp;
}

long long get_time(long long i,long long j) {
    return pref_sum_a[i] + pref_sum_b[j];
}

long long get_ans(long long nod,long long st,long long dr) {
    propag(nod,st,dr);
    if(st == dr) {
        return (aint[nod].val + aint[nod].base_offset);
    }

    long long mid = (st + dr) / 2;

    return get_ans(nod * 2,st,mid) + get_ans(nod * 2 + 1,mid + 1,dr);
}

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

long long i64() {
    long long ans = 0;
    long long sgn = 1;

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

    n = i64();
    m = i64();

    for(long long i = 1; i <= n; i++) {
        a[i] = i64();
        s[i] = i64();
        p[i] = i64();
        pref_sum_a[i] = a[i] + pref_sum_a[i - 1];
    }

    for(long long i = 1; i <= m; i++) {
        b[i] = i64();
        t[i] = i64();
        q[i] = i64();
        pref_sum_b[i] = b[i] + pref_sum_b[i - 1];
    }

    for(long long j = 0; j <= m; j++) {
        long long l = -1,r = n + 1;
        while(r - l > 1) {
            long long mid = (l + r) / 2;
            if(get_time(mid,j) <= t[j]) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        pref_col[j] =  l;
    }


    for(long long i = 0; i <= n; i++) {
        long long l = -1,r = m + 1;

        while(r - l > 1) {
            long long mid = (l + r) / 2;
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

    for(long long i = 1; i <= n; i++) {
        if(pref_lin[i] > -1) {
            update_offset(1,0,n,i,p[i],true);
            event[pref_lin[i] + 1].push_back(i);
        }
    }

    for(long long j = 1; j <= m; j++) {
        for(auto it:event[j]) {
            update_offset(1,0,n,it,-p[it]);
            if(-p[it] > 0) {
                long long k = get_pos_sum(it + 1,p[it]);
                if(k <= n) {
                    update_val(1,0,n,k,(query_sum(1,0,n,it + 1,k) + p[it]) - get_val(1,0,n,k));
                }
                if(it + 1 <= k - 1) {
                    update_0(1,0,n,it + 1,k - 1);
                }
            }
        }
        if(pref_col[j] > -1) {
            update_val(1,0,n,0,q[j]);
            long long k = get_pos_sum(pref_col[j] + 1,-q[j]);
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
