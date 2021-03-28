#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

const int NMAX = 1e5;

vector<int> graph[NMAX + 5];

int t;
int n,m;
int dist[NMAX + 5][2];

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

        while(!q.empty()){
            int nod = q.front().first;
            int side = q.front().second;
            q.pop();

            for(auto it:graph[nod]){
                int to = (side ^ 1);

                if(dist[it][to] == 0){
                    dist[it][to] = 1 + dist[nod][side];
                    q.push({it,to});
                }
            }
        }

        map<pair<int,int>,int > stuff;

        for(int i = 1;i <= n;i++){
            stuff[{dist[i][0],dist[i][1]}] = 0;
        }

        int ans = 0;
        int bi_ans = 0;

        for(int i = 2; i <= n;i++){
            if(dist[i][0] == 0 && dist[i][1] == 0){
                continue;
            }
            if(dist[i][0] == 0 || dist[i][1] == 0){
                ans++;
            }else{
                if(stuff.count({dist[i][1] - 1,dist[i][0] - 1})){
                    ans++;
                }else if(stuff.count({dist[i][1] - 1,dist[i][0] + 1})){
                    ans++;
                    stuff[{dist[i][1] - 1,dist[i][0] + 1}]--;
                    stuff[{dist[i][0],dist[i][1]}]++;
                }else{
                    ans += 2;
                }
            }
        }

        for(auto &it:stuff){
            bi_ans += ((max(0,it.second) + 1) / 2);
        }
            
        ans += bi_ans;

        printf("%d\n",ans);
    }

    return 0;
}
