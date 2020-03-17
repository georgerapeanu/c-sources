#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

FILE *f = fopen("aquapark.in","r");
FILE *g = fopen("aquapark.out","w");

const int NMAX = 70000;
const int MMAX = 100000;
const int MOD = 666013;

int c,n,m;
pair<int,int> edge[MMAX + 5];
set<pair<int,int>> graph[NMAX + 5];

vector<int> edge_graph[MMAX + 5];
int state[MMAX + 5];


void dfs(int nod,int st = 1){
    state[nod] = st;
    for(auto it:edge_graph[nod]){
        if(state[it] == 0){
            dfs(it,st ^ 2);
        }
    }
}

set<pair<int,int> > :: iterator it;

void solve(int st,int dr){
    printf("deb %d %d\n",st,dr);
    if(st > dr){
        return ;
    }

    if(graph[st].empty()){
        solve(st + 1,dr);
        return ;
    }

    vector<pair<int,int> > endpoints;

    if(graph[st].begin()->first != st + 1){
        endpoints.push_back({st + 1,0});
    }

    for(auto it:graph[st]){
        endpoints.push_back(it);
    }

    if(endpoints.back().first != dr){
        endpoints.push_back({dr,0});
    }

    for(auto it:graph[st]){
        graph[it.first].erase({st,it.second});
    }

    graph[st].clear();

    for(auto it:endpoints){
        printf("%d %d\n",it.first,it.second);
    }

    for(int i = 0;i + 2 < (int)endpoints.size();i++){
        if(endpoints[i + 1].first - endpoints[i].first < endpoints[i + 2].first - endpoints[i + 1].first){
            for(int st = endpoints[i].first;st < endpoints[i + 1].first;st++){
                it = graph[st].lower_bound({endpoints[i + 1].first + 1,0});
                while(it != graph[st].end() && it->first > endpoints[i + 1].first && it->first <= endpoints[i + 2].first){
                    edge_graph[endpoints[i + 1].second].push_back(it->second);
                    edge_graph[it->second].push_back(endpoints[i + 1].second);
                    it = next(it);
                    graph[prev(it)->first].erase({st,prev(it)->second});
                    graph[st].erase(prev(it));
                }
            }
        }
        else{
            for(int dr = endpoints[i + 2].second;dr > endpoints[i + 1].first;dr--){
                it = graph[dr].lower_bound({endpoints[i].first,0});
                while(it != graph[dr].end() && it->first >= endpoints[i].first && it->first < endpoints[i + 1].first){
                    edge_graph[it->second].push_back(endpoints[i + 1].second);
                    edge_graph[endpoints[i + 1].second].push_back(it->second);
                    it = next(it);
                    graph[prev(it)->first].erase({dr,prev(it)->second});
                    graph[dr].erase(prev(it));
                }
            }
        }
    }

    for(int i = 0;i < (int)endpoints.size() - 1;i++){
        solve(endpoints[i].first,endpoints[i + 1].first);
    }
}

int main(){

    fscanf(f,"%d %d %d",&c,&n,&m);

    for(int i = 1;i <= m;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);

        edge[i] = {x,y};

        set<pair<int,int>> :: iterator it = graph[x].lower_bound({y,0});
        if(it != graph[x].end() && it->first == y){
            edge_graph[i].push_back(it->second);
            edge_graph[it->second].push_back(i);
            graph[y].erase({x,it->second});
            graph[x].erase({y,it->second});
        }
        else{
            graph[x].insert({y,i});
            graph[y].insert({x,i});
        }
    }

    solve(1,n);

    int ans = 1;

    for(int i = 1;i <= m;i++){
        if(state[i] == 0){
            dfs(i);
            ans <<= 1;
            if(ans >= MOD){
                ans -= MOD;
            }
        }
    }

    if(c == 2){
        fprintf(g,"%d\n",ans);
    }
    else{
        for(int i = 1;i <= m;i++){
            fprintf(g,"%d %d %d\n",edge[i].first,edge[i].second,state[i]);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
