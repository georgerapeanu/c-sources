#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e6;
const int MOD = 1e9 + 7;

int n,m;
int last_node;
vector<pair<int,int> > graph[NMAX + 5];

void add_edge(int u,int v,int tmp) {
    vector<int> cf;
    while(tmp) {
        cf.push_back(tmp % 10);
        tmp /= 10;
    }
    reverse(cf.begin(),cf.end());
    if((int)cf.size() == 1) {
        graph[u].push_back({v,cf[0]});
    }
    else {
        graph[u].push_back({++last_node,cf[0]});
        for(int i = 1; i < (int)cf.size() - 1; i++) {
            graph[last_node].push_back({last_node + 1,cf[i]});
            last_node++;
        }
        graph[last_node].push_back({v,cf.back()});
    }
}

int val[NMAX + 5];
bool viz[NMAX + 5];

int main() {

    scanf("%d %d",&n,&m);
    last_node = n;

    for(int i = 1; i <= m; i++) {
        int u, v;
        int tmp = i;
        scanf("%d %d",&u,&v);
        add_edge(u,v,tmp);
        add_edge(v,u,tmp);
    }

    vector< vector<int> > bfs = {{1}};

    for(int i = 0; i < (int)bfs.size(); i++) {
        vector<pair<int,int> > v[10];
        for(auto it:bfs[i]) {
            for(auto it2:graph[it]) {
                v[it2.second].push_back({it,it2.first});
            }
        }
        for(int k = 0; k < 10; k++) {
            vector<int> tmp;
            for(auto it:v[k]) {
                if(viz[it.second] == false) {
                    viz[it.second] = true;
                    val[it.second] = (1LL * val[it.first] * 10 + k) % MOD;
                    tmp.push_back(it.second);
                }
            }
            if(tmp.empty() == false) {
                bfs.push_back(tmp);
            }
        }
    }

    for(int i = 2; i <= n; i++) {
        printf("%d\n",val[i]);
    }

    return 0;
}
