#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

struct dsu_t{
    int father[1505];
    int cnt_edges[1505];
    int cnt_nodes[1505];
    vector<int> dp[1505];

    dsu_t(int n){
        for(int i = 1;i <= n;i++){
            father[i] = 0;
            cnt_nodes[i] = 1;
            cnt_edges[i] = 0;
            dp[i] = {0,1};
        }
    }

    int find_root(int nod){
        if(father[nod] == 0){
            return nod;
        }
        return father[nod] = find_root(father[nod]);
    }

    void unite(int x,int y){
        x = find_root(x);
        y = find_root(y);

        if(x == y){
            cnt_edges[x]++;
            if(cnt_edges[x] == cnt_nodes[x] * (cnt_nodes[x] - 1) / 2){
                dp[x][1]++;
                if(dp[x][1] >= MOD){
                    dp[x][1] = 0;
                }
            }
            return ;
        }

        father[x] = y;
        cnt_nodes[y] += cnt_nodes[x];
        cnt_edges[y] += cnt_edges[x] + 1;

        vector<int> tmp((int)dp[x].size() + (int)dp[y].size() - 1,0);

        if(cnt_edges[y] == cnt_nodes[y] * (cnt_nodes[y] - 1) / 2){
            tmp[1]++;
        }

        for(int i = 0;i < (int)dp[x].size();i++){
            for(int j = 0;j < (int)dp[y].size();j++){
                tmp[i + j] = (tmp[i + j] + 1LL * dp[x][i] * dp[y][j]) % MOD;
            }
        }
        dp[y] = tmp;
    }
};

int n;
vector<pair<int,pair<int,int> > > edges;

int main() {

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            int val;
            scanf("%d",&val);
            if(i < j){
                edges.push_back({val,{i,j}});
            }
        }
    }

    sort(edges.begin(),edges.end());

    dsu_t dsu(n);

    for(auto it:edges){
        dsu.unite(it.second.first,it.second.second);
    }

    for(int i = 1;i <= n;i++){
        printf("%d ",dsu.dp[dsu.find_root(1)][i]);
    }


    return 0;
}
