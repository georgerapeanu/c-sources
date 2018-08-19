#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int N,S;

vector<int> V;
vector<int> nxt;
vector< pair<int,int> > G[200005];
bool viz[200005];
map<int,int> normalize;
vector< vector<int> > op;

vector<int> dfs(int nod){
    vector<int> tmp;
    while(!G[nod].empty()){
        int v = G[nod].back().first;
        int tag = G[nod].back().second;
        G[nod].pop_back();
        tmp = dfs(v);
        tmp.push_back(tag);
    }
    return tmp;
}

vector<vector<int> > solve(vector<int> V,vector<int> pula_cycle){
    op.clear();
    if(pula_cycle.size()){
        reverse(pula_cycle.begin(),pula_cycle.end());
        op.push_back(pula_cycle);
    }
    vector<int> sorted = V;
    sort(sorted.begin(),sorted.end());

    vector<int> NV,id;

    for(int i = 0;i < N;i++){
        if(sorted[i] != V[i]){
            id.push_back(i);
            NV.push_back(i);
        }
    }

    sort(NV.begin(),NV.end(),[&](int a,int b){return V[a] < V[b];});

    for(int i = 1;i <= N;i++){
        G[i].clear();
    }

    for(int i = 0;i < (int)NV.size();i++){
        int u = V[NV[i]];
        int v = V[id[i]];
        int tag = id[i];
        G[u].push_back({v,tag});
    }


    for(int i = 1;i <= N;i++){
        if(!G[i].empty()){
            vector<int> tmp = dfs(i);
            reverse(tmp.begin(),tmp.end());
            op.push_back(tmp);
        }
    }

    return op;
}

int main(){
    ///freopen("in","r",stdin);
 ///   freopen("out","w",stdout);
    cin >> N >> S;

    V.resize(N);
    nxt = vector<int>(N,-1);

    for(int i = 0;i < N;i++){
        cin >> V[i];
        normalize[V[i]] = 0;
    }

    int last = 0;

    for(auto &it:normalize){
        it.second = ++last;
    }

    for(auto &it:V){
        it = normalize[it];
    }

    int cnt = 0;

    vector<int> sorted = V;
    sort(sorted.begin(),sorted.end());

    for(int i = 0;i < N;i++){
        if(sorted[i] != V[i]){
            cnt++;
        }
    }



    if(cnt > S){
        cout << -1;
        return 0;
    }

    S -= cnt;

    solve(V,vector<int>());

    if(S > 1 && (int)op.size() > 1){
         vector<int> pula_cycle;
        for(int i = 0;i < min((int)op.size(),S);i++){
            pula_cycle.push_back(op[i].back());
        }

        for(int i = 0;i < (int)pula_cycle.size() - 1;i++){
            swap(V[pula_cycle[i]],V[pula_cycle[i + 1]]);
        }

        solve(V,pula_cycle);
    }

    cout << op.size() << "\n";
    for(auto it:op){
        cout << it.size() << "\n";
        for(auto it2:it){
            cout << it2 + 1 << " ";
        }
        cout << "\n";

    }
    return 0;
}
