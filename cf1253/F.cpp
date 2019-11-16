#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 3e5;

int n,k,m,q;
vector<pair<int,int> > graph[NMAX + 5];
long long dist[NMAX + 5];
int by_whom[NMAX + 5];
long long ans[QMAX + 5];

struct query_t {
    int id;
    int l,r;
    int u,v;

    bool operator < (const query_t &other)const {
        return l + r < other.l + other.r;
    }

} queries[QMAX + 5];

int dsu[NMAX + 5];

void reset_dsu() {
    memset(dsu,0,sizeof(dsu));
}

int fi_root(int x) {
    if(dsu[x] == 0) {
        return x;
    }
    return dsu[x] = fi_root(dsu[x]);
}

bool unite(int x,int y) {
    x = fi_root(x);
    y = fi_root(y);

    if(x == y) {
        return false;
    }

    dsu[x] = y;

    return true;
}

int main() {

    scanf("%d %d %d %d",&n,&m,&k,&q);

    for(int i = 1; i <= m; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        graph[a].push_back({b,c});
        graph[b].push_back({a,c});
    }

    priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > pq;

    for(int i = 1; i <= k; i++) {
        pq.push({0,i});
        dist[i] = 0;
        by_whom[i] = i;
    }

    vector<pair<long long,pair<int,int> > > s;

    while(!pq.empty()) {
        long long cost = pq.top().first;
        int nod = pq.top().second;
        pq.pop();

        if(cost != dist[nod]) {
            continue;
        }

        for(auto it:graph[nod]) {
            if(by_whom[it.first] == 0) {
                by_whom[it.first] = by_whom[nod];
                dist[it.first] = dist[nod] + it.second;
                pq.push({dist[it.first],it.first});
            }
            else {
                if(by_whom[it.first] != by_whom[nod]) {
                    s.push_back({0LL + dist[it.first] + dist[nod] + it.second,{by_whom[nod],by_whom[it.first]}});
                }
                if(dist[it.first] > dist[nod] + it.second) {
                    dist[it.first] = dist[nod] + it.second;
                    by_whom[it.first] = by_whom[nod];
                    pq.push({dist[it.first],it.first});
                }
            }
        }
    }

    sort(s.begin(),s.end());

    for(int i = 1; i <= q; i++) {
        scanf("%d %d",&queries[i].u,&queries[i].v);
        queries[i].l = -1;
        queries[i].r = (int)s.size() - 1;
        queries[i].id = i;
    }

    for(int h = 1; h <= 20; h++) {
        sort(queries + 1,queries + 1 + q);
        reset_dsu();
        int lst = -1;
        for(int i = 1; i <= q; i++) {
            while(lst < (queries[i].l + queries[i].r) / 2) {
                lst++;
                unite(s[lst].second.first,s[lst].second.second);
            }
            if(fi_root(queries[i].u) == fi_root(queries[i].v)) {
                queries[i].r = (queries[i].l + queries[i].r) / 2;
            }
            else {
                queries[i].l = (queries[i].l + queries[i].r) / 2;
            }
        }
    }

    for(int i = 1; i <= q; i++) {
        ans[queries[i].id] = s[queries[i].r].first;
    }

    for(int i = 1; i <= q; i++) {
        printf("%lld\n",ans[i]);
    }

    return 0;
}
