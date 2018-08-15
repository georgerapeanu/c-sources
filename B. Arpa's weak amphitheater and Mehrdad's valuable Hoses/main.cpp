#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct DSU_node{
    int father;
    int beauty_sum;
    int weight_sum;
    vector<int> hoses;
}DSU[1005];

int N,M,W;
int dp[1005][1005];
int weight[1005];
int beauty[1005];

vector<int> DSU_roots;

int find_root(int x){
    if(DSU[x].father == 0){
        return x;
    }
    return DSU[x].father = find_root(DSU[x].father);
}

void Union(int x,int y){
    x = find_root(x);
    y = find_root(y);

    if(x == y){
        return ;
    }

    DSU[x].father = y;
    DSU[y].beauty_sum += DSU[x].beauty_sum;
    DSU[y].weight_sum += DSU[x].weight_sum;
    for(auto it:DSU[x].hoses){
        DSU[y].hoses.push_back(it);
    }
}

int main(){

    scanf("%d %d %d",&N,&M,&W);

    for(int i = 1;i <= N;i++){
        scanf("%d",&weight[i]);
        DSU[i].weight_sum = weight[i];
        DSU[i].hoses.push_back(i);
    }

    for(int i = 1;i <= N;i++){
        scanf("%d",&beauty[i]);
        DSU[i].beauty_sum = beauty[i];
    }

    while(M--){
        int x,y;
        scanf("%d %d",&x,&y);
        Union(x,y);
    }

    for(int i = 1;i <= N;i++){
        if(DSU[i].father == 0){
            DSU_roots.push_back(i);
        }
    }

    for(int i = 0;i < (int)DSU_roots.size();i++){
        int root = DSU_roots[i];
        for(int j = 0;j <= W;j++){
            dp[i + 1][j] = max(dp[i][j],dp[i + 1][j]);

            if(j + DSU[root].weight_sum <= W){
                dp[i + 1][j + DSU[root].weight_sum] = max(dp[i][j] + DSU[root].beauty_sum,dp[i + 1][j + DSU[root].weight_sum]);
            }

            for(auto it:DSU[root].hoses){
                if(j + weight[it] <= W){
                    dp[i + 1][j + weight[it]] = max(dp[i + 1][j + weight[it]],dp[i][j] + beauty[it]);
                }
            }
        }
    }

    printf("%d",dp[(int)DSU_roots.size()][W]);

    return 0;
}
