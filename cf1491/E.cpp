#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int KMAX = 30;

int n;
int weight[NMAX + 5];
bool root[NMAX + 5];
vector<int> graph[NMAX + 5];
int fib[KMAX + 5];

void initdfs(int nod,int tata){
    int pos = -1;
    for(int i = 0;i < (int)graph[nod].size();i++){
        if(graph[nod][i] == tata){
            pos = i;
            continue;
        }
        initdfs(graph[nod][i],nod);
    }
    if(pos != -1){
        swap(graph[nod][pos],graph[nod][(int)graph[nod].size() - 1]);
        graph[nod].pop_back();
    }
}

void predfs(int nod,int target_value,vector<int> &ans){
    weight[nod] = 1;
    for(auto it:graph[nod]){
        if(root[it]){
            continue;
        }
        predfs(it,target_value,ans);
        weight[nod] += weight[it];
    }
    if(weight[nod] == target_value){
        ans.push_back(nod);
    }
}

bool dfs(int nod,int k){
    vector<int> tmp;
    tmp.clear();
    predfs(nod,fib[k - 1],tmp);
    if(weight[nod] != fib[k]){
        return false;
    }
    if(k <= 1){
        return true;
    }
    if(tmp.empty() == false){
        root[tmp[0]] = true;
        return dfs(nod,k - 2) && dfs(tmp[0],k - 1);
    }
    tmp.clear();
    predfs(nod,fib[k - 2],tmp);
    
    if(tmp.empty()){
        return false;
    }else if((int)tmp.size() == 1){
        root[tmp[0]] = true;
        return dfs(nod,k - 1) && dfs(tmp[0],k - 2);
    }else{
        root[tmp[0]] = true;
        root[tmp[1]] = true;
        return dfs(nod,k - 3) && dfs(tmp[0],k - 2) && dfs(tmp[1],k - 2);
    }
}

int main(){
    
    fib[0] = 1;
    fib[1] = 1;

    for(int i = 2;i <= KMAX;i++){
        fib[i] = fib[i - 2] + fib[i - 1];
    }


    scanf("%d",&n);
    
    for(int i = 1;i < n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    root[1] = true;
    initdfs(1,0);

    bool ok = false;

    for(int i = 0;i <= KMAX;i++){
        if(n == fib[i]){
            ok |= dfs(1,i); 
            break;
        }
    }

    printf(ok ? "YES\n":"NO\n");

    return 0;
}
