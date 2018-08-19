#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<int> G[300005];

int N,M;
int low[300005];
int lvl[300005];
bool viz[300005];

pair<int,int> dfs(int nod,int tata){
    viz[nod] = 1;
    low[nod] = lvl[nod];

    pair<int,int> best = {nod,0};

    for(auto it:G[nod]){
        if(it == tata){
            continue;
        }
        if(!viz[it]){
            lvl[it] = 1 + lvl[nod];
            pair<int,int> tmp = dfs(it,nod);
            low[nod] = min(low[nod],low[it]);
            if(tmp.second > best.second){
                best = tmp;
            }
        }
        else{
            low[nod] = min(low[nod],lvl[it]);
        }
    }

    if(tata && low[nod] > lvl[tata]){
        best.second++;
    }

    return best;

}

int main(){
    cin >> N >> M;

    for(int i = 1;i <= M;i++){
        int x,y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    pair<int,int> aux = dfs(1,0);
    memset(viz,0,sizeof(viz));
    pair<int,int> ans = dfs(aux.first,0);
    cout << ans.second;
    return 0;
}
