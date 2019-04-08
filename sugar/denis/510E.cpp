#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int NMAX = 200;
const int VMAX = 2e4;

int n;

int v[NMAX + 5];

int is_composite[VMAX + 5];

vector<int> graph[NMAX + 5];
int cap[NMAX + 5][NMAX + 5];
int flow[NMAX + 5][NMAX + 5];
int father[NMAX + 5];
int q[NMAX + 5],stq,drq;
int source = 0;
int dest = NMAX + 2;
int viz[NMAX + 5];

void add_edge(int u,int v,int cost) {
    graph[u].push_back(v);
    graph[v].push_back(u);
    cap[u][v] = cost;
}

int bfs(int source,int dest) {
    memset(father,0,sizeof(father));
    memset(viz,0,sizeof(viz));

    stq = 1;
    drq = 1;
    q[stq] = source;

    while(stq <= drq) {
        int nod = q[stq++];
        if(nod == dest) {
            continue;
        }
        for(auto it:graph[nod]) {
            if(viz[it] == false && flow[nod][it] < cap[nod][it]) {
                father[it] = nod;
                q[++drq] = it;
                viz[it] = true;
            }
        }
    }

    return viz[dest];
}

int max_flow(int source,int dest) {
    memset(flow,0,sizeof(flow));
    int mflow = 0;
    while(bfs(source,dest)) {
        for(auto it:graph[dest]) {
            if(flow[it][dest] < cap[it][dest]) {
                father[dest] = it;
                int fmin = 1 << 30;
                for(int nod = dest; nod != source; nod = father[nod]) {
                    fmin = min(fmin,cap[father[nod]][nod] - flow[father[nod]][nod]);
                }

                for(int nod = dest; nod != source; nod = father[nod]) {
                    flow[father[nod]][nod] += fmin;
                    flow[nod][father[nod]] -= fmin;
                }

                mflow += fmin;
            }
        }
    }

    return mflow;
}

int main() {

    for(int i = 2; i <= VMAX; i++) {
        if(is_composite[i] == false) {
            for(int j = i * i; j <= VMAX; j += i) {
                is_composite[j] = true;
            }
        }
    }

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    int even = 0,odd = 0;

    for(int i = 1; i <= n; i++) {
        if(v[i] % 2 == 0) {
            even++;
            add_edge(source,i,2);
            for(int j = 1; j <= n; j++) {
                if(is_composite[v[i] + v[j]] == false) {
                    add_edge(i,j,1);
                }
            }
        }
        else {
            odd++;
            add_edge(i,dest,2);
        }
    }

    if(max_flow(source,dest) != 2 * max(odd,even)) {
        printf("Impossible\n");
        return 0;
    }

    memset(viz,0,sizeof(viz));

    vector< vector<int> > ans;

    for(int i = 1; i <= n; i++) {
        if(viz[i] == true) {
            continue;
        }

        vector<int> comp;
        comp.push_back(i);
        viz[i] = true;

        for(int nod = i; true;) {
            bool found = false;
            for(int j = 1; j <= n; j++) {
                if(viz[j] == false && (flow[nod][j] == 1 || flow[j][nod] == 1)) {
                    comp.push_back(j);
                    nod = j;
                    viz[j] = true;
                    found = true;
                }
            }
            if(found == false) {
                break;
            }
        }

        ans.push_back(comp);

    }

    printf("%d\n",(int)ans.size());

    for(auto comp:ans) {
        printf("%d ",(int)comp.size());
        for(auto it:comp) {
            printf("%d ",it);
        }
        printf("\n");
    }

    return 0;
}
