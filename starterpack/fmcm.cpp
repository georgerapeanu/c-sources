#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

FILE *f = fopen("fmcm.in","r");
FILE *g = fopen("fmcm.out","w");

const int NMAX = 350;
const int MMAX = 12500;
const int inf = 1e9;

struct edge_t{
    int from;
    int to;
    int cap;
    int cst;
    int flow;
};

edge_t edges[2 * MMAX + 5];

int n,m,s,d;
int father[NMAX + 5];
int real_dist[NMAX + 5];
int dist[NMAX + 5];
int old_dist[NMAX + 5];
vector<int> graph[NMAX + 5];


queue<int> q;
bool inq[NMAX + 5];
bool bellman(int s,int d){

    for(int i = 1;i <= n;i++){
        inq[i] = false;
        real_dist[i] = inf;
    }

    inq[s] = true;
    real_dist[s] = 0;
    q.push(s);

    while(!q.empty()){
        int nod = q.front();
        q.pop();
        inq[nod] = false;

        if(nod == d){
            continue;
        }

        for(auto it:graph[nod]){
            if(edges[it].flow < edges[it].cap && real_dist[edges[it].to] > real_dist[nod] + edges[it].cst){
                real_dist[edges[it].to] = real_dist[nod] + edges[it].cst;
                if(inq[edges[it].to] == false){
                    inq[edges[it].to] = true;
                    q.push(edges[it].to);
                }
            }
        }
    }
    
    return real_dist[d] != inf; 
}

priority_queue<pair<int,int>,vector<pair<int,int> > ,greater<pair<int,int> > > pq;
bool dijkstra(int s,int d){
    for(int i = 1;i <= n;i++){
        old_dist[i] = real_dist[i];
        dist[i] = inf;
        real_dist[i] = inf;
        father[i] = 0;
    }

    dist[s] = 0;
    real_dist[s] = 0;
    pq.push({0,s});

    while(pq.empty() == false){
        int nod = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if(dist[nod] != cost){
            continue;
        }

        if(nod == d){
            break;
        }

        for(auto it:graph[nod]){
            if(edges[it].flow < edges[it].cap){
                int new_cost = cost + old_dist[edges[it].from] + edges[it].cst - old_dist[edges[it].to];

                if(new_cost < dist[edges[it].to]){
                    dist[edges[it].to] = new_cost;
                    real_dist[edges[it].to] = real_dist[nod] + edges[it].cst;
                    father[edges[it].to] = it;
                    pq.push({new_cost,edges[it].to});
                }
            }
        }
    }

    return dist[d] != inf;
}

long long fmcm(int s,int d){
    long long ans = 0;

    for(bellman(s,d);dijkstra(s,d);){
        int fmin = inf;
        for(int nod = d;nod != s;nod = edges[father[nod]].from){
            fmin = min(fmin,edges[father[nod]].cap - edges[father[nod]].flow);
        }
        ans += 1LL * fmin * real_dist[d];
        for(int nod = d;nod != s;nod = edges[father[nod]].from){
            edges[father[nod]].flow += fmin;
            edges[father[nod] ^ 1].flow -= fmin;
        }
    }

    return ans;
}

int main(){
   
    fscanf(f,"%d %d %d %d",&n,&m,&s,&d);

    for(int i = 0;i < m;i++){
        int x,y,c,z;
        fscanf(f,"%d %d %d %d",&x,&y,&c,&z);
      
        edges[2 * i] = {x,y,c,z,0};
        edges[2 * i + 1] = {y,x,0,-z,0};

        graph[x].push_back(2 * i);
        graph[y].push_back(2 * i + 1);
    }

    fprintf(g,"%lld\n",fmcm(s,d));

    fclose(f);
    fclose(g);

    return 0;
}
