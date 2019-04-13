#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int NMAX = 1e5;
const int BUCK = 100;

int n,m,q;
vector<pair<int,int> > edges[NMAX + 5];

int father[NMAX + 5];

int find_root(int nod) {
    if(father[nod] == 0) {
        return nod;
    }

    return father[nod] = find_root(father[nod]);
}

bool unite(int x,int y) {
    x = find_root(x);
    y = find_root(y);

    if(x == y) {
        return false;
    }

    father[x] = y;
    return true;
}

pair<int,int> queries[NMAX + 5];
int ans[NMAX + 5];

map<pair<int,int>,int> ans2;

int nodes[2 * NMAX + 5],len;

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        edges[c].push_back({a,b});
    }

    scanf("%d",&q);

    for(int i = 1; i <= q; i++) {
        scanf("%d %d",&queries[i].first,&queries[i].second);
    }

    for(int i = 1; i <= m; i++) {
        len = 0;
        for(auto it:edges[i]) {
            unite(it.first,it.second);
            nodes[++len] = it.first;
            nodes[++len] = it.second;
        }

        if(len <= BUCK) {
            sort(nodes + 1,nodes + 1 + len);
            len = unique(nodes + 1,nodes + 1 + len) - (nodes + 1);

            for(int i = 1; i <= len; i++) {
                for(int j = 1; j < i; j++) {
                    if(find_root(nodes[i]) == find_root(nodes[j])) {
                        ans2[ {nodes[i],nodes[j]}]++;
                    }
                }
            }
        }
        else {
            for(int j = 1; j <= q; j++) {
                ans[j] += (find_root(queries[j].first) == find_root(queries[j].second));
            }
        }

        for(int i = 1; i <= len; i++) {
            father[nodes[i]] = 0;
        }
    }

    for(int j = 1; j <= q; j++) {
        if(ans2.count(queries[j])) {
            ans[j] += ans2[queries[j]];
        }
        if(ans2.count({queries[j].second,queries[j].first})) {
            ans[j] += ans2[ {queries[j].second,queries[j].first}];
        }
        printf("%d\n",ans[j]);
    }

    return 0;
}
