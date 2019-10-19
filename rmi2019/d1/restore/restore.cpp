#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n,m;
int l[5005];
int r[5005];
int s[5005];

vector<pair<int,pair<int,int> > > graph[5005];

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int x,y,k,d;
        scanf("%d %d %d %d",&x,&y,&k,&d);
        x++;
        y++;
        if(d == 0){
            graph[x - 1].push_back({y,{1,(y - x + 1) - k}});
            graph[y].push_back({x - 1,{0,-(y - x + 1) + k}});
        }
        else{
            graph[x - 1].push_back({y,{0,(y - x + 1) - k + 1}});
            graph[y].push_back({x - 1,{1,-(y - x + 1) + k - 1}});
        }
    }
    
    for(int i = 0;i < n;i++){
        graph[i].push_back({i + 1,{0,0}});
        graph[i].push_back({i + 1,{1,1}});
        graph[i + 1].push_back({i,{1,0}});
        graph[i + 1].push_back({i,{0,-1}});
    }

    for(int i = 1;i <= n;i++){
        l[i] = 0;
        r[i] = n;
    }

    vector<int> q = {0};

    l[0] = r[0] = 0;

    for(int i = 0;i < (int)q.size();i++){
        int nod = q[i];
        for(auto it:graph[nod]){
            int to = it.first;
            int typ = it.second.first;
            int cost = it.second.second;
            if(typ == 0){
                if(l[to] < l[nod] + cost){
                    l[to] = l[nod] + cost;
                    if(l[to] > r[to]){
                        printf("-1\n");
                        return 0;
                    }
                    q.push_back(to);
                }
            }
            else{
                if(r[to] > r[nod] + cost){
                    r[to] = r[nod] + cost;
                    q.push_back(to);
                    if(l[to] > r[to]){
                        printf("-1\n");
                        return 0;
                    }
                }
            }
        }
    }

    for(int i = 0;i <= n;i++){
        if(l[i] > r[i]){
            printf("-1\n");
            return 0;
        }
    }
    
    for(int i = 1;i <= n;i++){
        printf("%d ",l[i] - l[i - 1]);
    }

    return 0;
}
