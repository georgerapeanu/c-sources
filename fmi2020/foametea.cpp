#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

FILE *f = fopen("foametea.in","r");
FILE *g = fopen("foametea.out","w");

struct edge_t {
    int to,l,c;
};

struct data_t {
    int node,sarmale;
    long long l;

    bool operator < (const data_t &other)const {
        if(l != other.l) {
            return l > other.l;
        }
        return sarmale < other.sarmale;
        return node < other.node;
    }
};

const int NMAX = 5000;
const int KMAX = 30;
const int MMAX = 25000;

int n,m,k;
int s[NMAX + 5];
long long dist[NMAX + 1][KMAX + 1];

vector<edge_t> graph[NMAX + 5];

int main() {

    fscanf(f,"%d %d %d",&n,&m,&k);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&s[i]);
    }

    while(m--) {
        int u,v,l,c;
        fscanf(f,"%d %d %d %d",&u,&v,&l,&c);
        graph[u].push_back({v,l,c});
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            dist[i][j] = 1e9;
        }
    }

    priority_queue<data_t> pq;

    for(int val = 0; val <= s[1]; val++) {
        dist[1][val] = 0;
        pq.push({1,val,0});
    }

    while(!pq.empty()) {
        data_t tmp = pq.top();
        pq.pop();
        if(tmp.l != dist[tmp.node][tmp.sarmale]) {
            continue;
        }
        if(tmp.node == n) {
            fprintf(g,"%lld\n",tmp.l);
            return 0;
        }
        for(auto it:graph[tmp.node]) {
            if(tmp.sarmale < it.c) {
                continue;
            }
            for(int val = 0; val <= s[it.to]; val++) {
                int to = it.to;
                int sarmale = tmp.sarmale - it.c + val;
                if(sarmale > k) {
                    break;
                }
                long long cost = tmp.l + it.l * ((sarmale - val) * (sarmale - val) + 1LL);
                if(dist[to][sarmale] > cost) {
                    dist[to][sarmale] = cost;
                    pq.push({to,sarmale,cost});
                }
            }
        }
    }

    fprintf(g,"Fomistul moare de foame\n");

    fclose(f);
    fclose(g);

    return 0;
}
