#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 1e3;

int n,m;
string s[NMAX + 5];

int last[NMAX + 5];
int tmp_id[NMAX + 5];
int l_tmp;
int last_node = 0;
vector<int> graph2[NMAX * NMAX + 5];

bool viz[NMAX * NMAX + 5];
int dp[NMAX * NMAX + 5];

void dfs(int nod){
    viz[nod] = true;
    dp[nod] = 1;
    for(auto it:graph2[nod]){
        dfs(it);
        dp[nod] = 1LL * dp[nod] * dp[it] % MOD;
    }
    dp[nod] = (dp[nod] + 1 == MOD ? 0:dp[nod] + 1);
}

vector<pair<int,int> > graph[NMAX * NMAX + 5][2];
bool viz2[NMAX * NMAX + 5][2];

int main(){
    freopen("cave.in","r",stdin);
    freopen("cave.out","w",stdout);
    cin >> n >> m;

    for(int i = 1;i <= n;i++){
        cin >> s[i];
        s[i] = " " + s[i];
    }

    for(int i = n;i;i--){
        //for(int j = 1;j <= m;j++)cout << last[j];cout << endl;
        for(int j = 1;j <= m;j++){
            if(last[j] && s[i][j] != '#'){
                graph[last[j]][1].push_back({j,0});
                graph[j][0].push_back({last[j],1});
            }
            if(j < m && s[i][j] != '#' && s[i][j + 1] != '#'){
                graph[j][0].push_back({j + 1,0});
                graph[j + 1][0].push_back({j,0});
            }
        }
        for(int j = 1;j <= m;j++){
            if(s[i][j] != '#' && viz2[j][0] == false){
                queue<pair<int,int> > q;
                last_node++;
                vector<int> sons;
                q.push({j,0});
                while(!q.empty()){
                    pair<int,int> tmp = q.front();q.pop();
                    if(tmp.second == 0){
                        tmp_id[tmp.first] = last_node;
                    }
                    else{
                        sons.push_back(tmp.first);
                    }
                    for(auto it:graph[tmp.first][tmp.second]){
                        if(viz2[it.first][it.second] == false){
                            q.push(it);
                            viz2[it.first][it.second] = true;
                        }
                    }
                }
                graph2[last_node].swap(sons);
            }
        }
        for(int j = 1;j <= m;j++){
            last[j] = tmp_id[j];
            tmp_id[j] = 0;
            viz2[last[j]][1] = false;
            viz2[j][0] = false;
            graph[j][0].clear();
            graph[last[j]][1].clear();
        }
    }

    int ans = 1;

    for(int i = last_node;i;i--){
        if(viz[i] == false){
            dfs(i);
            ans = 1LL * ans * dp[i] % MOD;
        }
    }

    cout << ans << "\n";

    return 0;
}
