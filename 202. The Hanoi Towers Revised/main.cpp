#include<iostream>
#include<cassert>
#include<vector>

using namespace std;
long long dp[100][100];
int ant[100][100];
int N,M;
vector<int> G[100];
void Move(int x,int S,int D){
    cout << "move " << x << " from " << S << " to " << D;
    if(!G[D].empty()){
        cout << " atop " << G[D].back();
    }
    assert(G[S].size() && G[S].back() == x);
    G[S].pop_back();
    G[D].push_back(x);
    cout << "\n";
}
void hanoi(int st,int dr,int S,int D,int aux){
    if(st == dr){
        Move(st,S,D);
        return;
    }
    hanoi(st,dr - 1,S,aux,D);
    Move(dr,S,D);
    hanoi(st,dr - 1,aux,D,S);
}
void solve(int N,int M,int st,int dr,int S,int D,vector<int> &poles){
    if(M <= 1 || N <= 0){
        return;
    }
    if(M == 2){
        Move(st,S,D);
        return ;
    }
    assert(poles.size() > 2);
    if(M == 3){
        assert((S == poles[0] || S == poles[1] || S == poles[2]) && (D == poles[0] || D == poles[1] || D == poles[2]));
        hanoi(st,dr,S,D,poles[0] ^ poles[1] ^ poles[2] ^ S ^ D);
        return ;
    }
    if(N == 1){
        Move(st,S,D);
        return ;
    }
    vector<int> new_poles;
    int found = 0;
    for(int i = 0;i < (int)poles.size();i++){
        if(!found && S != poles[i] && D != poles[i]){
            found = poles[i];
        }
        else{
            new_poles.push_back(poles[i]);
        }
    }
    int k = ant[N][M];
    solve(k,M,st,st + k - 1,S,found,poles);
    solve(N - k,M - 1,st + k,dr,S,D,new_poles);
    solve(k,M,st,st + k - 1,found,D,poles);
}
int main(){
    for(int i = 1;i <= 64;i++){
        for(int j = 0;j <= 65;j++){
            dp[i][j] = 1LL << 60;
        }
        dp[i][2] = (i == 1 ? 1 : 1LL << 60);
        for(int j = 3;j <= 65;j++){
            for(int k = 0;k < i;k++){
                if(dp[i][j] > dp[k][j] * 2 + dp[i - k][j - 1]){
                    dp[i][j] = dp[k][j] * 2 + dp[i - k][j - 1];
                    ant[i][j] = k;
                }
            }
        }
    }
    cin >> N >> M;
    cout << dp[N][M] << "\n";
    vector<int> poles;
    for(int i = 1;i <= M;i++){
        poles.push_back(i);
    }
    for(int i = N;i;i--){
        G[1].push_back(i);
    }
    solve(N,M,1,N,1,M,poles);
    return 0;
}
