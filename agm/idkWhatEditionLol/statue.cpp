#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 1e5;

int n,m;
long long r;

pair<int,int> pos[NMAX + 5];
pair<int,int> edge[MMAX + 5];
int cst[MMAX + 5];

pair<int,int> get_range(int x,pair<int,int> nod) {
    long long cost = r - (nod.first - x) * (nod.first - x);
    if(cost < 0) {
        return {1,0};
    }
    long long val = sqrt(cost);
    if(1LL * (val + 1) * (val + 1) <= cost) {
        val++;
    }
    return {nod.second - val,nod.second + val};
}

pair<int,int> get_sect(pair<int,int> a,pair<int,int> b) {
    return {max(a.first,b.first),min(a.second,b.second)};
}

int main() {

    scanf("%d %d %lld",&n,&m,&r);

    vector<pair<int,int> > events;
    events.reserve(2 * m);

    r = 1LL * r * r;

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&pos[i].first,&pos[i].second);
    }

    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d",&edge[i].first,&edge[i].second,&cst[i]);
    }

    long long ans = 0;

    for(int x = 0; x <= 100; x++) {
        events.clear();
        for(int i = 1; i <= m; i++) {
            pair<int,int> range = get_sect(get_range(x,pos[edge[i].first]),get_range(x,pos[edge[i].second]));
            if(range.first <= range.second) {
                events.push_back({range.first,cst[i]});
                events.push_back({range.second + 1,-cst[i]});
            }
        }
        sort(events.begin(),events.end());

        long long tmp = 0;

        for(auto it:events) {
            tmp += it.second;
            ans = max(ans,tmp);
        }
    }

    printf("%lld\n",ans);

    return 0;
}
