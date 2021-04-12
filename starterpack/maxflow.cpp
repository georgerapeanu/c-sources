#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1000;
const int MMAX = 5000;

struct edge_t{
    int from;
    int to;
    int flow;
    int cap;
};


int n,m;
edge_t edges[2 * MMAX + 5];
int father[NMAX + 5];
bool viz[NMAX + 5];
vector<int> graph[NMAX + 5];
int q[NMAX + 5];
int stq,drq;

int maxflow(int s,int d){
    
    int ans = 0;

    while(true){
        for(int i = 1;i <= n;i++){
            viz[i] = false;
            father[i] = 0;
        }
        q[stq = drq = 1] = s;
        viz[s] = true;

        while(stq <= drq){
            int nod = q[stq++];

            if(nod == d){
                continue;
            }

            for(auto it:graph[nod]){
                if(edges[it].flow < edges[it].cap && viz[edges[it].to] == false){
                    father[edges[it].to] = it;
                    viz[edges[it].to] = 1;
                    q[++drq] = edges[it].to;
                }
            }
        }

        if(viz[d] == false){
            break;
        }
        
        for(auto it:graph[d]){
            if(edges[it ^ 1].flow < edges[it ^ 1].cap && viz[edges[it ^ 1].from] == true){
                father[d] = it ^ 1;
                int fmin = 1e9;

                for(int nod = d;nod != s;nod = edges[father[nod]].from){
                    fmin = min(fmin,edges[father[nod]].cap - edges[father[nod]].flow);
                }

                for(int nod = d;nod != s;nod = edges[father[nod]].from){
                    edges[father[nod]].flow += fmin;
                    edges[father[nod] ^ 1].flow -= fmin;
                }

                ans += fmin;
            }
        }
    }

    return ans;
}

int main(){
    
    freopen("maxflow.in","r",stdin);
    freopen("maxflow.out","w",stdout);

    scanf("%d %d",&n,&m);

    for(int i = 0;i < m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        edges[2 * i] = {a,b,0,c};
        edges[2 * i + 1] = {b,a,0,0};
        graph[a].push_back(2 * i);
        graph[b].push_back(2 * i + 1);
    }

    printf("%d\n",maxflow(1,n));

    return 0;
}
