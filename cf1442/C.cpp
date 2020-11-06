#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int MOD = 998244353;
const int LGMAX = 17;

int n,m;
vector<int> graph[2][NMAX + 5];

deque<int> q;

int dist[NMAX + 5];

deque<pair<int,int> > stuff;
int dp[NMAX + 5][LGMAX + 1];

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        graph[0][x].push_back(y);
        graph[1][y].push_back(x);
    }

    for(int i = 1;i <= n;i++){
        dist[i] = 1e9;
    }

    dist[1] = 0;
    q.push_back(1);

    while(!q.empty()){
        int nod = q.front();
        int t = (dist[nod] & 1);
        q.pop_front();

        for(auto it:graph[t][nod]){
            if(dist[it] > dist[nod]){
                dist[it] = dist[nod];
                q.push_front(it);
            }
        }
        for(auto it:graph[t ^ 1][nod]){
            if(dist[it] > dist[nod] + 1){
                dist[it] = dist[nod] + 1;
                q.push_back(it);
            }
        }
    } 

    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= LGMAX;j++){
            dp[i][j] = 1e9;
        }
    }

    stuff.push_back({1,0});
    dp[1][0] = 0;

    while(!stuff.empty()){
        pair<int,int> tmp = stuff.front();
        stuff.pop_front();
        if(tmp.second < LGMAX && dp[tmp.first][tmp.second + 1] > dp[tmp.first][tmp.second]){
            dp[tmp.first][tmp.second + 1] = dp[tmp.first][tmp.second];
            stuff.push_front({tmp.first,tmp.second + 1});
        }
        for(auto it:graph[(dist[tmp.first] + tmp.second) & 1][tmp.first]){
            int to = tmp.second + dist[tmp.first] - dist[it];
            if(0 <= to && to <= LGMAX && dp[tmp.first][tmp.second] + 1 < dp[it][to]){
                dp[it][to] = 1 + dp[tmp.first][tmp.second];
                stuff.push_back({it,to});
            }
        }
    }

    int ans = 1e9;
    int pw2 = 1;

    for(int i = 1;i <= dist[n];i++){
        pw2 += pw2;
        if(pw2 >= MOD){
            pw2 -= MOD;
        }
    }

    pw2--;
    for(int i = 0;i <= LGMAX;i++){ 
        ans = min(ans,(dp[n][i] + pw2) % MOD);
        pw2 += pw2 + 1;
        if(pw2 >= MOD){
            pw2 -= MOD;
        }
        if(dist[n] + i > 0 && (dist[n] >= 30 || (n >> (dist[n] + i - 1)) == 0)){
            break;
        }
    }

    printf("%d\n",ans);

    return 0;
}
