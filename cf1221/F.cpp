#include <bits/stdc++.h>

using namespace std;

const long long NMAX = 5e5;
const long long LEAFS = 2 * NMAX;

long long n;
pair<long long,long long> v[NMAX + 5];

bool cmp(pair<long long,long long> a,pair<long long,long long> b) {
    return min(a.first,a.second) > min(b.first,b.second);
}

map<long long,long long> to_norm;
map<pair<long long,long long> ,long long> cst;

struct node_t {
//    long long best_sum;
    long long total_sum;
    long long best_pref_sum;
    long long pref_id;
//    long long best_suff_sum;

    node_t() {
        //      best_sum = 0;
        total_sum = 0;
        best_pref_sum = 0;
        //      best_suff_sum = 0;
        pref_id = 0;
    }

    node_t operator + (const node_t &other)const {
        node_t ans;

        ans.total_sum = this->total_sum + other.total_sum;
        if(this->best_pref_sum > this->total_sum + other.best_pref_sum) {
            ans.best_pref_sum = this->best_pref_sum;
            ans.pref_id = this->pref_id;
        }
        else {
            ans.best_pref_sum = this->total_sum + other.best_pref_sum;
            ans.pref_id = other.pref_id;
        }
//        ans.best_suff_sum = max(other.best_suff_sum,this->best_suff_sum + other.total_sum);
//        ans.best_sum = max(max(this->best_sum,other.best_sum),this->best_suff_sum + other.best_pref_sum);

        return ans;
    }
};

node_t aint[4 * LEAFS + 5];

void update(long long nod,long long st,long long dr,long long pos,long long val,long long id) {
    if(dr < pos || st > pos) {
        return ;
    }
    if(st == dr) {
        //      aint[nod].best_sum += val;
        aint[nod].best_pref_sum += val;
        //      aint[nod].best_suff_sum += val;
        aint[nod].total_sum += val;
        aint[nod].pref_id = id;
        return ;
    }

    long long mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val,id);
    update(nod * 2 + 1,mid + 1,dr,pos,val,id);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

node_t query(long long nod,long long st,long long dr,long long l,long long r) {
    if(r < st || l > dr) {
        return node_t();
    }
    if(l <= st && dr <= r) {
        return aint[nod];
    }

    long long mid = (st + dr) / 2;

    return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
}

void afis(long long nod,long long st,long long dr) {
    printf("%lld %lld %lld %lld\n",nod,st,dr,aint[nod].best_pref_sum);
    if(st == dr) {
        return ;
    }

    long long mid = (st + dr) / 2;

    afis(nod * 2,st,mid);
    afis(nod * 2 + 1,mid + 1,dr);
}

int main() {

    scanf("%lld",&n);

    for(int i = 1; i <= n; i++) {
        long long c;
        scanf("%lld %lld %lld",&v[i].first,&v[i].second,&c);
        to_norm[v[i].first] = 1;
        to_norm[v[i].second] = 1;
        cst[v[i]] += c;
    }

    sort(v + 1,v + 1 + n);
    n = unique(v + 1,v + 1 + n) - (v + 1);

    sort(v + 1,v + 1 + n,cmp);

    long long last = 0;
    long long lx = -1;

    for(auto &it:to_norm) {
        it.second = ++last;
        if(lx != -1) {
            update(1,1,(long long)to_norm.size(),last,-(it.first - lx),it.first);
        }
        lx = it.first;
    }

    long long ans = 0;
    long long x = 0,y = 0;

    while(cst.count({x,y})) {
        x++;
        y++;
    }

    for(int i = 1; i <= n; i++) {
        update(1,1,last,to_norm[max(v[i].first,v[i].second)],cst[v[i]],max(v[i].first,v[i].second));
        if(i == n || min(v[i].first,v[i].second) != min(v[i + 1].first,v[i + 1].second)) {
            node_t tmp = query(1,1,last,to_norm[min(v[i].first,v[i].second)] + 1,last);
            tmp.best_pref_sum += cst[ {min(v[i].first,v[i].second),min(v[i].first,v[i].second)}];
            if(tmp.pref_id == 0) {
                tmp.pref_id = min(v[i].second,v[i].first);
            }
            if(tmp.best_pref_sum > ans) {
                ans = tmp.best_pref_sum;
                x = min(v[i].first,v[i].second);
                y = tmp.pref_id;
            }
        }
    }

    printf("%lld\n",ans);
    printf("%lld %lld %lld %lld\n",x,x,y,y);

    return 0;
}
