#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int dp[1 << ('z' - 'a')];
vector< pair<int,char> > G[500005];
int modifier[500005];
int ans[500005];
int lvl[500005];
int weight[500005];
int best[500005];
int RootNodeXor[500005];

void predfs(int nod){
    weight[nod] = 1;
    for(auto it:G[nod]){
        lvl[it.first] = lvl[nod] + 1;
        RootNodeXor[it.first] = RootNodeXor[nod] ^ (1 << (it.second - 'a'));
        predfs(it.first);
        weight[nod] += weight[it.first];
        if(best[nod] == 0 || weight[it.first] > weight[best[nod]]){
            best[nod] = it.first;
        }
    }
}

vector<int> subtree(int node){
    vector<int> nodes;
    nodes.push_back(node);
    for(int i = 0;i < (int)nodes.size();i++){
        for(auto it:G[nodes[i]]){
            nodes.push_back(it.first);
        }
    }
    return nodes;
}

void dfs(int nod,bool dump){
    if(G[nod].empty()){
        if(dump)return;
        dp[RootNodeXor[nod]] = max(dp[RootNodeXor[nod]],lvl[nod]);
        return ;
    }

    for(auto it:G[nod]){
        if(it.first != best[nod]){
            dfs(it.first,1);
            ans[nod] = max(ans[nod],ans[it.first]);
        }
    }

    dfs(best[nod],0);
    ans[nod] = max(ans[nod],ans[best[nod]]);
    for(int target_state = 1;target_state <= (1 << ('v' - 'a'));target_state *= 2){
        ans[nod] = max(ans[nod],dp[target_state ^ RootNodeXor[nod]] - lvl[nod]);
    }
    ans[nod] = max(ans[nod],dp[RootNodeXor[nod]] - lvl[nod]);

    dp[RootNodeXor[nod]] = max(dp[RootNodeXor[nod]],lvl[nod]);

    for(auto it:G[nod]){
        if(it.first != best[nod]){
            vector<int> V = subtree(it.first);
            for(auto it2:V){
                for(int target_state = 1;target_state <= (1 << ('v' - 'a'));target_state *= 2){
                    ans[nod] = max(ans[nod],lvl[it2] + dp[target_state ^ RootNodeXor[it2]] - 2 * lvl[nod]);
                }
                ans[nod] = max(ans[nod],lvl[it2] + dp[RootNodeXor[it2]] - 2 * lvl[nod]);
            }

            for(auto it2:V){
                dp[RootNodeXor[it2]] = max(dp[RootNodeXor[it2]],lvl[it2]);
            }
        }
    }

    if(dump){
        vector<int> V = subtree(nod);
        for(auto it:V){
            dp[RootNodeXor[it]] = -(1 << 28);
        }
    }

}

int main(){

    for(int i = 0;i < (1 << ('z' - 'a'));i++){
        dp[i] = -(1 << 28);
    }

    scanf("%d",&N);

   for(int i = 2;i <= N;i++){
        int p;
        char c;
        scanf("%d %c",&p,&c);
        G[p].push_back({i,c});
    }

    lvl[1] = 1;

    predfs(1);
    dfs(1,1);

    for(int i = 1;i <= N;i++){
        printf("%d ",ans[i]);
    }

    return 0;
}
