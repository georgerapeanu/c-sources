#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int NMAX = 2e5;

int n,k;
pair<int,int> v[NMAX + 5];
int t[NMAX + 5];
int last;

map<int,int> to_norm;

vector<pair<pair<int,int>,int> > query[3 * NMAX + 5];
vector<int> update[3 * NMAX + 5];
int aib[3 * NMAX + 5];
int aint[6 * NMAX + 5];

void update_aib(int pos,int val) {
    for(; pos <= last; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int query_aib(int pos) {
    if(pos <= 0) {
        return 0;
    }
    int ans = 0;
    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }
    return ans;
}

void update_aint(int pos,int v) {
    pos += last;
    aint[pos] = max(aint[pos],v);
    for(; pos > 1; pos >>= 1) {
        aint[pos >> 1] = max(aint[pos],aint[pos ^ 1]);
    }
}

int query_aint(int l,int r) {
    int ans = 0;

    for(l += last,r += (last + 1); l < r; (l >>= 1),(r >>= 1)) {
        if(l % 2)ans = max(ans,aint[l++]);
        if(r % 2)ans = max(ans,aint[--r]);
    }

    return ans;
}


int main() {

    scanf("%d %d",&n,&k);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&v[i].first,&v[i].second);
        to_norm[v[i].first] = 1;
        to_norm[v[i].second] = 1;
    }

    for(int i = 1; i <= k; i++) {
        scanf("%d",&t[i]);
        to_norm[t[i]] = 1;
    }

    last = 0;
    for(auto &it:to_norm) {
        it.second = ++last;
    }

    for(int i = 1; i <= k; i++) {
        update_aint(to_norm[t[i]],i);
    }

    for(int i = 1; i <= n; i++) {
        int n_a = to_norm[v[i].first];
        int n_b = to_norm[v[i].second];

        if(n_a == n_b) {
            query[n_a].push_back({v[i],0});
        }
        else if(n_a < n_b) {
            int tmp = query_aint(n_a,n_b - 1);
            if(tmp > 0) {
                swap(v[i].first,v[i].second);
            }
            query[n_b].push_back({v[i],tmp});
        }
        else {
            int tmp = query_aint(n_b,n_a - 1);
            query[n_a].push_back({v[i],tmp});
        }
    }

    for(int i = 1; i <= k; i++) {
        update[to_norm[t[i]]].push_back(i);
    }

    int cnt = 0;
    long long ans = 0;

    for(int i = last; i >= 0; i--) {
        for(auto it:update[i]) {
            update_aib(it,1);
            cnt++;
        }
        for(auto it:query[i]) {
            if((cnt - query_aib(it.second - 1)) & 1) {
                ans += it.first.second;
            }
            else {
                ans += it.first.first;
            }
        }
    }

    printf("%lld\n",ans);

    return 0;
}
