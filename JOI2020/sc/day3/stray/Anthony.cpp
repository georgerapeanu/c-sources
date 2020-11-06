//#include "Anthony.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

const int NMAX = 20000;

int viz[NMAX + 5];
vector<pair<int,int> > graph[NMAX + 5];
int a,b;
vector<int> secv = {0,1,0,0,1,1};
vector<int> ans;
int dist[NMAX + 5];

void dfs(int nod,int tata,int ind){
    queue<pair<pair<int,int>,int> > q;
    q.push({{nod,tata},ind});
    viz[nod] = true;
    while(!q.empty()){
        pair<pair<int,int>,int> tmp = q.front();
        q.pop();
        int nod = tmp.first.first;
        int tata = tmp.first.second;
        int ind = tmp.second;
        for(auto it:graph[nod]){
            if(it.first == tata){
                continue;
            }
            if(viz[it.first]){
                if(dist[it.first] < dist[nod]){
                    ans[it.second] = ind;
                }
                else{
                    ans[it.second] = (ind + 1) % 3;
                }
            }
            else{
                if(a == 3){
                    ans[it.second] = (ind + 1) % 3;
                    viz[it.first] = true;
                    dist[it.first] = 1 + dist[nod];
                    q.push({{it.first,nod},(ind + 1) % 3});
                }
                else{
                    ans[it.second] = secv[ind];
                    viz[it.first] = true;
                    dist[it.first] = 1 + dist[nod];
                    q.push({{it.first,nod},(graph[it.first].size() == 2 ? ((ind + 1) % 6):(1 - secv[ind]))});
                }
            }
        }
    }
}

vector<int> Mark(int N, int M, int A, int B,vector<int> U, vector<int> V) {
    
    a = min(3,A);
    b = B;

    ans = vector<int>(M,1);

    for(int i = 0;i < M;i++){
        graph[U[i]].push_back({V[i],i});
        graph[V[i]].push_back({U[i],i});
    }

    dfs(0,-1,0);
    
    //for(int i = 0;i < M;i++)printf("%d %d %d\n",U[i],V[i],ans[i]);printf("\n");

    return ans;
}
