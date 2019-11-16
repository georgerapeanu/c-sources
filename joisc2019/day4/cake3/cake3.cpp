#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int NMAX = 2e5;

int n,m;
pair<int,int> v[NMAX + 5];

vector<int> vals;

map<int,int> stuff;

pair<long long,int> aib[NMAX + 5];

void update(int pos,pair<int,int> val) {
    pos = (int)vals.size() - pos + 1;///for enhanced binary searche
    for(; pos <= (int)vals.size(); pos += (-pos) & pos) {
        aib[pos].first += val.first;
        aib[pos].second += val.second;
    }
}

long long get_best_sum(int cnt) {
    pair<long long,int> lst = {0,0};
    int pos = 0;

    for(int h = 1 << 18; h; h >>= 1) {
        if(pos + h <= (int)vals.size() && lst.second + aib[pos + h].second < cnt) {
            pos += h;
            lst.first += aib[pos].first;
            lst.second += aib[pos].second;
        }
    }
    lst.first += 1LL * (cnt - lst.second) * vals[(int)vals.size() - pos - 1];
    return lst.first;
}

int ins_cnt;

void add(pair<int,int> a) {
    ins_cnt++;
    stuff[a.second]++;
    update(lower_bound(vals.begin(),vals.end(),a.first) - vals.begin() + 1, {a.first,1});
}

void rem(pair<int,int> a) {
    ins_cnt--;
    stuff[a.second]--;
    if(stuff[a.second] == 0) {
        stuff.erase(a.second);
    }
    update(lower_bound(vals.begin(),vals.end(),a.first) - vals.begin() + 1, {-a.first,-1});
}

long long query(int cnt) {
    if(cnt > ins_cnt) {
        return -1e18;
    }
    long long ans = -stuff.rbegin()->first + stuff.begin()->first + get_best_sum(cnt);
    return ans;
}

int st = 1,dr = 0;
long long calc(int l,int r) {
    while(st > l) {
        add(v[--st]);
    }
    while(dr < r) {
        add(v[++dr]);
    }
    while(st < l) {
        rem(v[st++]);
    }
    while(dr > r) {
        rem(v[dr--]);
    }
    return query(m);
}

long long solve(int st,int dr,int lo,int hi) {

    if(st > dr) {
        return -1e18;
    }

    int mid = (st + dr) / 2;
    pair<long long,int> bst = {-1e18,0};
    for(int i = max(lo,mid); i <= hi; i++) {
        bst = max(bst, {calc(mid,i),i});
    }

    if(st == dr) {
        return bst.first;
    }

    return max(max(solve(st,mid - 1,lo,bst.second),solve(mid + 1,dr,bst.second,hi)),bst.first);
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&v[i].first,&v[i].second);
        v[i].second *= 2;
        vals.push_back(v[i].first);
    }

    sort(vals.begin(),vals.end());
    vals.resize(unique(vals.begin(),vals.end()) - vals.begin());

    sort(v + 1,v + 1 + n,[&]
    (const pair<int,int> &a,const pair<int,int> &b) {
        if(a.second != b.second) {
            return a.second < b.second;
        }
        return a.first < b.first;
    });

    printf("%lld\n",solve(1,n - m + 1,m,n));


    return 0;
}


