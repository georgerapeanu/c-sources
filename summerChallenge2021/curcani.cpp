#include <bits/stdc++.h>

using namespace std;

FILE *f = fopen("curcani.in","r");
FILE *g = fopen("curcani.out","w");

const int NMAX = 250;
const int MMAX = 1000;
const int KMAX = 5;

const long long inf = 1e18;

int n,m,k;
long long dist[NMAX + 5];

struct edge_t{
  int u,v,w;
  int other(int nod){
    return u ^ v ^ nod;
  }
};

edge_t edges[MMAX + 5];

vector<int> graph[NMAX + 5];

int a[MMAX + 5][KMAX + 1];

class MaxFlowSolver{
  struct edge_t{
    int u,v;
    long long cap,flow;
  };
  vector<edge_t> edges;
  vector<vector<int> > graph;

  vector<int> viz;
  vector<int> father;
  queue<int> q;

  bool bfs(int source,int destination){
    for(auto &it:viz){
      it = 0;
    }
    for(auto &it:father){
      it = 0; 
    }
  
    while(q.empty() == false){
      q.pop();
    }


    viz[source] = 1;
    q.push(source);

    while(!q.empty()){
      int nod = q.front();
      q.pop();
      
      if(nod == destination){
        continue;
      }

      for(auto it:graph[nod]){
        if(edges[it].flow < edges[it].cap && viz[edges[it].v] == false){
          viz[edges[it].v] = 1;
          father[edges[it].v] = it;
          q.push(edges[it].v);
        }
      }
    }

    return viz[destination];
  }

public:
  int source;
  int destination;

  MaxFlowSolver(int n){
    edges.clear();
    graph = vector<vector<int> >(n + 2,vector<int>(0,0));
    source = 0;
    destination = n + 1;

    q = queue<int>();
    father = vector<int>(n + 2,0);
    viz = vector<int>(n + 2,0);
  }

  void addEdge(int x,int y,long long cap){
    edges.push_back({x,y,cap,0});
    edges.push_back({y,x,0,0});
    graph[x].push_back((int)edges.size() - 2);
    graph[y].push_back((int)edges.size() - 1);
  }

  long long getMaxFlow(){

    long long maxflow = 0;

    while(bfs(source,destination)){
      for(auto it:graph[destination]){
        if(viz[edges[it ^ 1].u] && edges[it ^ 1].flow < edges[it ^ 1].cap){
          father[destination] = it ^ 1;
          long long fmin = 1e18;
          for(int nod = destination;nod != source;nod = edges[father[nod]].u){
            fmin = min(edges[father[nod]].cap - edges[father[nod]].flow,fmin);
          }
          maxflow += fmin;
          for(int nod = destination;nod != source;nod = edges[father[nod]].u){
            edges[father[nod]].flow += fmin;
            edges[father[nod] ^ 1].flow -= fmin;
          }
        }
      }
    }

    return maxflow;
  }
};

void dijkstra(int s,int d){
  for(int i = 1;i <= n;i++){
    dist[i] = inf;
  }
  dist[s] = 0;
  priority_queue<pair<long long,int> , vector<pair<long long,int> >, greater<pair<long long,int> > > pq;
  pq.push({dist[s],s});

  while(pq.empty() == false){
    pair<long long,int> tmp = pq.top();
    pq.pop();
    int nod = tmp.second;
    long long cost = tmp.first;

    if(cost != dist[nod]){
      continue;
    }

    for(auto it:graph[nod]){
      if(dist[edges[it].v] > dist[nod] + edges[it].w){
        dist[edges[it].v] = dist[nod] + edges[it].w;
        pq.push({dist[edges[it].v],edges[it].v});
      }
    }
  } 
}

inline pair<int,int> getVirtualEdgeNodes(int edge,int elevation){

  return {n * k + ((edge - 1) * k + elevation) * 2 + 1, n * k + ((edge - 1) * k + elevation) * 2 + 2};
}

inline int getVirtualNode(int node,int elevation){
  return (node - 1) * k + elevation + 1;
}

int main(){

  fscanf(f,"%d %d %d",&n,&m,&k);

  for(int i = 1;i <= m;i++){
    fscanf(f,"%d %d %d",&edges[i].u,&edges[i].v,&edges[i].w);
    graph[edges[i].u].push_back(i);
  }

  for(int i = 1;i <= m;i++){
    for(int j = 1;j <= k;j++){
      fscanf(f,"%d",&a[i][j]);
    }
  }

  dijkstra(1,n);

  MaxFlowSolver solver(n * k);

  for(int i = 1;i <= m;i++){
    int h = dist[edges[i].u] + edges[i].w - dist[edges[i].v];
    for(int u_elevation = 0;u_elevation < k;u_elevation++){
      for(int edge_elevation = 0;edge_elevation + u_elevation + h < k;edge_elevation++){
        int v_elevation = h + u_elevation + edge_elevation; 
        solver.addEdge(getVirtualNode(edges[i].u,u_elevation),getVirtualNode(edges[i].v, v_elevation),a[i][edge_elevation + 1] - a[i][edge_elevation]);
      }
    }
  }

  solver.addEdge(solver.source,getVirtualNode(1,0),inf);

  for(int h = 0;h < k;h++){
    solver.addEdge(getVirtualNode(n,h),solver.destination,inf);
  }

  fprintf(g,"%lld\n",solver.getMaxFlow());

  fclose(f);
  fclose(g);

  return 0;
}
