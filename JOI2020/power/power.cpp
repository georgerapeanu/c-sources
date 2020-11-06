#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
vector<int> graph[200005];
string s;

int dp[200005];
int sum[200005];

void predfs(int nod,int tata){
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        predfs(it,nod);
        sum[nod] += dp[it];
    }

    if(s[nod] == '1'){
        dp[nod] = max(1,sum[nod] - 1);
    }
    else{
        dp[nod] = sum[nod];
    }
}

int ans = 0;

void dfs(int nod,int tata){
    ans = max(ans,dp[nod]);

    for(auto it:graph[nod]){
        ans = max(ans,dp[it] + (s[nod] == '1'));
    }

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }

        sum[nod] -= dp[it];
        if(s[nod] == '1'){
            dp[nod] = max(1,sum[nod] - 1);
        }
        else{
            dp[nod] = sum[nod];
        }
        sum[it] += dp[nod];
        if(s[it] == '1'){
            dp[it] = max(1,sum[it] - 1);
        }
        else{
            dp[it] = sum[it];
        }

        dfs(it,nod);

        sum[it] -= dp[nod];
        if(s[it] == '1'){
            dp[it] = max(1,sum[it] - 1);
        }
        else{
            dp[it] = sum[it];
        }

        sum[nod] += dp[it];
        if(s[nod] == '1'){
            dp[nod] = max(1,sum[nod] - 1);
        }
        else{
            dp[nod] = sum[nod];
        }
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

    cin >> s;

    s = " " + s;

    predfs(1,0);
    dfs(1,0);

    cout << ans << "\n";

    return 0;
}
