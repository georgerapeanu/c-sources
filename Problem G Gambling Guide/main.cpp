#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N,M;
vector<int> G[300005];
double E[300005];
bool viz[300005];
const double eps = 1e-7;
int gr[300005];

int main(){

    scanf("%d %d",&N,&M);

    while(M--){
        int x,y;
        scanf("%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for(int i = 1;i < N;i++){
        gr[i] = G[i].size();
        E[i] = gr[i];
    }

    viz[N] = 1;
    priority_queue<pair<double,int>,vector<pair<double,int> >,greater<pair<double,int> > > H;
    H.push({0,N});
    while(!H.empty()){
        int nod = H.top().second;
        double dist = H.top().first;
        H.pop();
        if(abs(E[nod] / (G[nod].size() - gr[nod]) - dist) > eps){
            continue;
        }
        E[nod] = dist;
        viz[nod] = 1;
        for(auto it:G[nod]){
            if(!viz[it]){
                E[it] += E[nod];
                gr[it]--;
                H.push({E[it] / (G[it].size() - gr[it]),it});
            }
        }
    }

    printf("%.7f",E[1]);

    return 0;
}
