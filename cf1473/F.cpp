#include <bits/stdc++.h>

using namespace std;

class MaximumFlowSolver{
    
    struct edge_t{
        int from;
        int to;
        int cap;
        int flow;
    };

    int n;
    int s;
    int d;

    vector<edge_t> edges;
    vector<int> viz;
    vector<vector<int> > graph;

    vector<int> father;
    
    bool bfs(){
        queue<int> q;
        for(auto &it:viz){
            it = 0;
        }
        for(auto &it:father){
            it = -1;
        }

        q.push(s);
        viz[s] = 1;

        while(!q.empty()){
            int nod = q.front();
            q.pop();
            if(nod == d){
                continue;
            }
            for(auto it:graph[nod]){
                if(viz[edges[it].to] == false && edges[it].flow < edges[it].cap){
                    father[edges[it].to] = it;
                    viz[edges[it].to] = 1;
                    q.push(edges[it].to);
                }
            }
        }
        return viz[d];
    }

public:
    
    MaximumFlowSolver(int n){
        this->n;
        this->graph = vector<vector<int> >(n + 3);
        this->edges = vector<edge_t>();
        this->viz = vector<int>(n + 3);
        this->father = vector<int>(n + 3);
        this->s = 0;
        this->d = n + 1;
    }

    void add_edge(int a,int b,int cap){
        if(a == -1){
            a = s;
        }
        if(b == -1){
            b = d;
        }
        edges.push_back({a,b,cap,0});
        edges.push_back({b,a,0,0});
        graph[a].push_back((int)edges.size() - 2);
        graph[b].push_back((int)edges.size() - 1);
    }

    int max_flow(){
        int flow = 0;

        while(bfs()){
            for(auto it:graph[d]){
                if(viz[edges[it ^ 1].from] && edges[it ^ 1].flow < edges[it ^ 1].cap){
                    int fmin = 1e9;
                    father[d] = (it ^ 1);
                    for(int nod = d;nod != s;nod = edges[father[nod]].from){
                        fmin = min(fmin,edges[father[nod]].cap - edges[father[nod]].flow);
                    }
                    flow += fmin;
                    for(int nod = d;nod != s;nod = edges[father[nod]].from){
                        edges[father[nod]].flow += fmin;
                        edges[father[nod] ^ 1].flow -= fmin;
                    }
                }
            }
        }

        return flow;
    }

};

const int NMAX = 3000;
const int VMAX = 100;

int last[VMAX + 1];

int n;
int a[NMAX + 5];
int b[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
    }
    
    for(int i = 1;i <= n;i++){
        scanf("%d",&b[i]);
    }

    MaximumFlowSolver solver(n);

    int ans = 0;

    for(int i = 1;i <= n;i++){
        if(b[i] > 0){
            solver.add_edge(i,-1,b[i]);
            ans += b[i];
        }else if(b[i] < 0){
            solver.add_edge(-1,i,-b[i]);
        }
        for(int val = 1;val <= a[i];val++){
            if(last[val] != 0 && a[i] % val == 0){
                solver.add_edge(last[val],i,1e9);
            }
        }
        last[a[i]] = i;
    }

    printf("%d\n",ans - solver.max_flow());

    return 0;
}
