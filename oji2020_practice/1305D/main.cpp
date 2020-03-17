#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1005;

int n;

vector<int> graph[NMAX + 5];

bool can_be[NMAX + 5];

int ask(int u,int v){
    int ans;
    cout << "? " << u << " " << v << endl;
    cin >> ans;
    if(ans == -1){
        exit(0);
    }
    return ans;
}

void answer(int nod){
    cout << "! " << nod << endl;
    exit(0);
}

int dfs(int nod,int tata,bool lant){

    for(int i = 0;i < (int)graph[nod].size();i++){
        if(graph[nod][i] == tata){
            swap(graph[nod][i],graph[nod].back());
            break;
        }
    }

    if(graph[nod].size() && graph[nod].back() == tata){
        graph[nod].pop_back();
    }

    while((int)graph[nod].size() > 1){
        int u = graph[nod][(int)graph[nod].size() - 1];
        int v = graph[nod][(int)graph[nod].size() - 2];
        int w = ask(u,v);
        if(w == nod){
            graph[nod].pop_back();
            graph[nod].pop_back();
        }
        else if(w == u){
            return dfs(u,nod,lant);
        }
        else{
            return dfs(v,nod,lant);
        }
    }

    if(graph[nod].empty()){
        return nod;
    }

    if(lant){
        return dfs(graph[nod][0],nod,lant);
    }
    else{
        int u = dfs(graph[nod][0],nod,true);
        return ask(nod,u);
    }
}

int main(){

    cin >> n;

    for(int i = 1;i < n;i++){
        int x,y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    answer(dfs(1,0,false));

    return 0;
}
