#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;
const int MMAX = 2e5;

int n,m;
int k;

vector<int> graph[NMAX + 5];
vector<int> t_graph[NMAX + 5];

vector<int> path;

int min_dist[NMAX + 5];
queue<int> q;

int mi[NMAX + 5];
int ma[NMAX + 5];

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        graph[a].push_back(b);
        t_graph[b].push_back(a);
    }

    scanf("%d",&k);

    for(int i = 1;i <= k;i++){
        int a;
        scanf("%d",&a);
        path.push_back(a);
    }

    min_dist[path.back()] = 1;
    q.push(path.back());

    while(!q.empty()){
        int nod = q.front();
        q.pop();

        for(auto it:t_graph[nod]){
            if(min_dist[it] == 0){
                min_dist[it] = min_dist[nod] + 1;
                q.push(it);
            }
        }
    }

    mi[k - 1] = ma[k - 1] = 0;

    for(int i = k - 2;i >= 0;i--){
        mi[i] = mi[i + 1] + (min_dist[path[i]] != min_dist[path[i + 1]] + 1);
        ma[i] = ma[i + 1];

        for(auto it:graph[path[i]]){
            if(it != path[i + 1] && min_dist[it] + 1 == min_dist[path[i]]){
                ma[i]++;
                break;
            }
        }
    }

    printf("%d %d\n",mi[0],ma[0]);

    return 0;
}
