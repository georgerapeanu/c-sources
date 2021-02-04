#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int LGMAX = 30;
const int NMAX = 1e4;

int n;
int m;
int c0;

int values[LGMAX + 1][NMAX + 1];
vector<pair<int,int> > graph[NMAX + 5];
int dist[NMAX + 5];
int cost_now[NMAX + 5];

inline int calculate_cost(int nod,int low){
    int h = 0;

    while(values[h][nod] > low){
        h++;
    }
    return h;
}

bool ok(int low){
    priority_queue<pair<int,int> > pq;
    for(int i = 1;i <= n;i++){
        dist[i] = -1;
        cost_now[i] = calculate_cost(i,low);
    }

    dist[1] = c0 - cost_now[1];

    if(dist[1] >= 0){
        pq.push({dist[1],1});
    }

    while(pq.empty() == false){
        int nod = pq.top().second;
        int coins = pq.top().first;
        pq.pop();

        if(dist[nod] != coins){
            continue;
        }

        for(auto it:graph[nod]){
            int to = it.first;
            int new_coins = coins + it.second - cost_now[to];
            if(new_coins > dist[to]){
                dist[to] = new_coins;
                pq.push({dist[to],to});
            }
        }
    }

    return dist[n] >= 0;
}

int main(){
    scanf("%d %d %d",&n,&m,&c0);

    for(int i = 1;i <= n;i++){
        scanf("%d",&values[0][i]);
        for(int h = 1;h <= LGMAX;h++){
            values[h][i] = (values[h - 1][i] >> 1);
        }
    }

    while(m--){
        int x,y,c;
        scanf("%d %d %d",&x,&y,&c);
        x++;
        y++;
        graph[x].push_back({y,c});
    }

    int st = -1;
    int dr = 1e9 + 1;

    while(dr - st > 1){
        
        int mid = (st + dr) / 2;

        if(ok(mid)){
            dr = mid;
        }else{
            st = mid;
        }
    }

    printf("%d\n",dr);

    return 0;
}
