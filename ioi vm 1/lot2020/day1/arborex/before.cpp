#include <vector>

#include <algorithm>
#include <cstdio>

using namespace std;

const int NMAX = 2e5;
const int BUCK = 45;

vector<pair<int,int>> graph[NMAX + 5];
vector<pair<int,int>> graph2[NMAX + 5];

vector<int> vals[NMAX + 5];
int brut_dp[NMAX + 5][2];
int weight[NMAX + 5];

void predfs(int nod,int tata){
    weight[nod] = 1;

    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        predfs(it.first,nod);
        weight[nod] += weight[it.first];
    }
}




void brut(int nod,int tata,int k){
    brut_dp[nod][0] = brut_dp[nod][1] = 1;
    vector<int> sons;
    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        brut(it.first,nod,k);
        sons.push_back(brut_dp[it.first][1] + it.second);
    }
    sort(sons.begin(),sons.end());
    reverse(sons.begin(),sons.end());

    for(int i = 1;i < (int)sons.size();i++){
        sons[i] += sons[i - 1];
    }

    for(int i = 0;i <= k && i <= (int)sons.size();i++){
        int son_dp = (i > 0 ? sons[i - 1]:0);
        int val1_dp = 0;
        int val2_dp = 0;
        if(vals[nod].size() == 0){
            ;
        }
        else if(k - i - 1 >= (int)vals[nod].size()){
            val1_dp = vals[nod].back();
        }
        else if(k - i - 1 >= 0){
            val1_dp = vals[nod][k - i - 1];
        }
        if(vals[nod].size() == 0){
            ;
        }
        else if(k - i - 2 >= (int)vals[nod].size()){
            val2_dp = vals[nod].back();
        }
        else if(k - i - 2 >= 0){
            val2_dp = vals[nod][k - i - 2];
        }
        brut_dp[nod][0] = max(brut_dp[nod][0],1 + son_dp + val1_dp);
        if(i != k){
            brut_dp[nod][1] = max(brut_dp[nod][1],1 + son_dp + val2_dp);
        }
    }
}

vector<int> nodes;
int dfs(int nod,int tata){
    bool special = ((int)graph[nod].size() > BUCK);///such a shame he lost in warchest
    vector<pair<int,int> > roots;

    vector<int> possible_vals;

    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        int tmp = dfs(it.first,nod);
        if(tmp != -1){
            roots.push_back({tmp,it.first});
        }
        else{
            possible_vals.push_back(weight[it.first]);
        }
    }

    if((int)roots.size() > 1 || tata == 0){
        special = true;
    }

    if(special){
        vals[nod] = possible_vals;
        sort(vals[nod].begin(),vals[nod].end());
        reverse(vals[nod].begin(),vals[nod].end());
        for(int i = 1;i < (int)vals[nod].size();i++){
            vals[nod][i] += vals[nod][i - 1];
        }
        for(auto it:roots){
            int to = it.first;
            int val = weight[it.second] - weight[to];
            graph2[nod].push_back({to,val});
            graph2[to].push_back({nod,val});
        }
        nodes.push_back(nod);
        return nod;
    }
    else{
        if((int)roots.size() == 0){
            return -1;
        }
        else{
            return roots[0].first;
        }
    }
}

vector<int> solve(int n, vector<int> a, vector<int> b) {
    std::vector<int> ret(n);

    for(int i = 0;i < (int)a.size();i++){
        graph[a[i]].push_back({b[i],0});
        graph[b[i]].push_back({a[i],0});
    }

    predfs(1,0);

    for(int i = 1;i <= n && i <=  BUCK;i++){
        brut(1,0,i);
        int ma = 0;
        for(int j = 1;j <= n;j++){
            ma = max(ma,brut_dp[j][0]);
        }
        ret[i - 1] = ma;
    }

    int root = dfs(1,0);

    for(int i = 1;i <= n;i++){
        graph[i].swap(graph2[i]);
    }

    for(int i = BUCK + 1;i <= n;i++){
        brut(root,0,i);
        int ma = 0;
        
        for(auto it:nodes){
            ma = max(ma,brut_dp[it][0]);
        }
        ret[i - 1] = ma;
    }

    return ret;
    
}
