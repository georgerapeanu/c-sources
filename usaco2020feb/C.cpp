#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>


using namespace std;

const int NMAX = 1e5;

vector<int> graph[NMAX + 5];

int t;
int n,m;
int dist[NMAX + 5][2];
int fr[2 * NMAX + 5][2];

int main(){
    
    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);

        for(int i = 1;i <= n;i++){
            dist[i][0] = dist[i][1] = 0;
            graph[i].clear();
        }

        for(int i = 1;i <= m;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        queue<pair<int,int> > q;

        dist[1][0] = 1;
        q.push({1,0});
        fr[0][0] = 1;

        int ans = 1;
        while(!q.empty()){
            int nod = q.front().first;
            int side = q.front().second;
            fr[dist[nod][side]][side]++;
            ans = 1LL * ans * fr[dist[nod][side] - 1]
            q.pop();

            for(auto it:graph[nod]){
                int to = (side ^ 1);

                if(dist[it][to] == 0){
                    dist[it][to] = 1 + dist[it][nod];
                    q.push({it,to});
                    ans++;
                }
            }
        }

        printf("%d\n",ans);
    }

    return 0;
}
