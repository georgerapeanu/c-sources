#include <iostream>
#include <vector>
using namespace std;
bool relic[1000005];
int dp[1000005];
int num[1000005];
bool viz[1000005];
vector<int> G[1000005];
int N,M,P;
void dfs(int nod){
    if(viz[nod]){
        return;
    }
    viz[nod] = 1;
    if(G[nod].size() == 0){
        num[nod] = (nod == N);
        dp[nod] = relic[nod];
        return ;
    }
    int mx = -1;
    for(auto it:G[nod]){
        dfs(it);
        mx = max(mx,dp[it]);
    }
    for(auto it:G[nod]){
        if(dp[it] == mx){
            num[nod] += num[it];
            if(num[nod] >= (1e9) + 7){
                num[nod] -= ((1e9) + 7);
            }
        }
    }
    dp[nod] = mx + relic[nod];
}
int main(){
    cin >> N >> M >> P;
    for(int i = 1;i <= P;i++){
        int x;
        cin >> x;
        relic[x] = 1;
    }
    for(int i = 1;i <= M;i++){
        int x,y;
        cin >> x >> y;
        G[x].push_back(y);
    }
    dfs(1);
    cout << num[1];
    return 0;
}
