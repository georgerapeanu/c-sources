#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 100;
const int MMAX = 5e3;

int n,m;
int lvl[NMAX + 5];
vector<pair<int,int> > graph[NMAX + 5];
vector<pair<double,int>> events[NMAX + 5];
set<double> stuff;
double cap[NMAX + 5];
double max_flow[NMAX + 5]; 

void dfs(int nod,int tata){
    lvl[nod] = 1 + lvl[tata];

    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        if(lvl[it.first] == 0){
            dfs(it.first,nod);        
        }
    }
}

int main(){
    
    freopen("flux.in","r",stdin);
    freopen("flux.out","w",stdout);

    scanf("%d %d",&n,&m);

    while(m--){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        graph[a].push_back({b,c});
        graph[b].push_back({a,c});
    }

    dfs(1,0);

    if(lvl[n] == 0){
        printf("%.6f\n",0);
        return 0;
    }

    for(int i = 1;i <= n;i++){
        for(auto it:graph[i]){
            if(lvl[it.first] > lvl[i]){
                events[lvl[i]].push_back({it.second / double(lvl[it.first] - lvl[i]),0});
                events[lvl[it.first]].push_back({it.second / double(lvl[it.first] - lvl[i]),1});
            }
        }
    }

    for(int i = 1;i < lvl[n];i++){
        for(auto it:events[i]){
            if(it.second == 0){
                stuff.insert(it.first);
            }else{
                stuff.erase(it.first);
            }
        }
        cap[i] = *stuff.rbegin();        
    }



    return 0;
}
