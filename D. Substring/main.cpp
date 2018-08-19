#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
vector<int> sortaret;
vector<int> G[300005];
int gr[300005];
int N,M;
string a;
queue<int> Q;
int pasi;
int rez;
int dp[300005];
int rundp(int c){
    int rez = 0;
    memset(dp,0,sizeof(dp));
    for(auto it:sortaret){
        dp[it] = (a[it] == c + 'a');
        for(auto it2:G[it]){
            dp[it] = max(dp[it],dp[it2] + (a[it] == c + 'a'));
        }
        rez = max(rez,dp[it]);
    }
    return rez;
}
int main(){
    cin >> N >> M;
    cin >> a;
    a = " " + a;
    while(M--){
        int x,y;
        cin >> x >> y;
        gr[y]++;
        G[x].push_back(y);
    }
    for(int i = 1;i <= N;i++){
        if(!gr[i]){
            Q.push(i);
        }
    }
    while(!Q.empty()){
        int nod = Q.front();Q.pop();
        sortaret.push_back(nod);
        pasi++;
        for(auto it:G[nod]){
            gr[it]--;
            if(!gr[it]){
                Q.push(it);
            }
        }
    }
    if(pasi < N){
        cout << -1;
        return 0;
    }
    reverse(sortaret.begin(),sortaret.end());
    for(int i = 0;i < 26;i++){
        rez = max(rez,rundp(i));
    }
    cout << rez;
    return 0;
}
