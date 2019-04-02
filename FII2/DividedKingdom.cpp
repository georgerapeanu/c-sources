#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 2.5e5;

int n,m;

vector<pair<int,int> > graph[NMAX + 5];

struct edge_t {
    int x,y,z;

    bool operator < (const edge_t &other) {
        return z < other.z;
    }
};

edge_t edges[MMAX + 5];

int comp[NMAX + 5];
int tag[NMAX + 5];
int weight[NMAX + 5];

void dfs(int nod,int old_c,int new_c,int sw) {
    tag[nod] ^= sw;
    comp[nod] = new_c;

    for(auto it:graph[nod]) {
        if(comp[it.first] == old_c) {
            dfs(it.first,old_c,new_c,sw);
        }
    }
}

int main() {
    cin >> n >> m;

    for(int i = 1; i <= m; i++) {
        cin >> edges[i].x >> edges[i].y >> edges[i].z;
    }


    sort(edges + 1,edges + 1 + m);

    for(int i = 1; i <= m; i++) {
        int x = edges[i].x;
        int y = edges[i].y;
        int z = edges[i].z;

        if(!comp[x]) {
            comp[x] = x;
            weight[x] = 1;
            tag[x] = 1;
        }

        if(!comp[y]) {
            comp[y] = y;
            weight[y] = 1;
            tag[y] = 1;
        }

        if(comp[x] != comp[y]) {
            if(weight[comp[x]] > weight[comp[y]]) {
                swap(x,y);
            }
            weight[comp[y]] += weight[comp[x]];
            dfs(x,comp[x],comp[y],(tag[x] == tag[y]));
        }
        else if(tag[x] != tag[y]) {
            ;
        }
        else {
            int ans = z;

            for(int i = 1; i <= n; i++) {
                int mi1 = 1 << 30,mi2 = 1 << 30;

                for(auto it:graph[i]) {
                    if(it.second < mi1) {
                        mi2 = mi1;
                        mi1 = it.second;
                    }
                    else if(it.second < mi2) {
                        mi2 = it.second;
                    }
                }

                if(mi2 != (1 << 30)) {
                    ans = min(ans,mi1 + mi2);
                }
            }

            cout << (ans == (1 << 30) ? -1:ans);
            return 0;
        }

        graph[x].push_back({y,z});
        graph[y].push_back({x,z});

    }

    int ans = 1 << 30;

    for(int i = 1; i <= n; i++) {
        int mi1 = 1 << 30,mi2 = 1 << 30;

        for(auto it:graph[i]) {
            if(it.second < mi1) {
                mi2 = mi1;
                mi1 = it.second;
            }
            else if(it.second < mi2) {
                mi2 = it.second;
            }
        }

        if(mi2 != (1 << 30)) {
            ans = min(ans,mi1 + mi2);
        }
    }

    cout << (ans == (1 << 30) ? -1:ans);

    return 0;
}
