#include <bits/stdc++.h>

using namespace std;

int n,m;
vector<string> v;
vector< vector<int> > viz;
vector< vector<pair<int,int>> > dp;///first point where a split is possible,where all the paths meet,-1 if no split point yet,-2 if impossible

pair<int,int> get_(pair<int,int> a,pair<int,int> b){
    if(a.first == -1 || b.first == -1){
        return {-1,-1};
    }
    if(a == b){
        return a;
    }
    if(a > b){
        swap(a,b);
    }
    return dp[a.first][a.second] = get_(dp[a.first][a.second],b);
}

bool bfs(int stx,int sty,int drx,int dry){
    
    for(int i = stx;i <= drx;i++){
        for(int j = sty;j <= dry;j++){
            viz[i][j] = false;
            dp[i][j] = {-1,-1};
        }
    }

    viz[drx][dry] = true;

    for(int i = drx;i >= stx;i--){
        for(int j = dry;j >= sty;j--){
            if(v[i][j] == '#'){
                continue;
            }
            if(i + 1 <= n){
                viz[i][j] |= viz[i + 1][j];
            }
            if(j + 1 <= m){
                viz[i][j] |= viz[i][j + 1];
            }
            
            bool ok_down = (i + 1 <= n && v[i + 1][j] == '.' && viz[i + 1][j] == true);
            bool ok_right = (j + 1 <= m && v[i][j + 1] == '.' && viz[i][j + 1] == true);

            if(ok_down && ok_right){
                dp[i][j] = get_(dp[i + 1][j],dp[i][j + 1]);
            }
            else if(ok_down){
                dp[i][j] = {i + 1,j};
            }
            else if(ok_right){
                dp[i][j] = {i,j + 1};
            }
            else{
                dp[i][j] = {-1,-1};
            }
        }
    }

    return viz[stx][sty];
}

int main() {
    
    cin >> n >> m;

    v.resize(n + 1);
    viz.resize(n + 1);
    dp.resize(n + 1);

    for(int i = 1;i <= n;i++){
        cin >> v[i];
        v[i] = " "  + v[i];
        viz[i].resize(m + 1);
        dp[i].resize(m + 1);
    }

    if(bfs(1,1,n,m) == false){
        cout << "0\n";
        return 0;
    }
    else{
        if(n == 1 || m == 1 || viz[1][2] == false || viz[2][1] == false || (dp[1][1] != make_pair(-1,-1) && dp[1][1] != make_pair(n,m))){
            cout << "1\n";
            return 0;
        }
        
        cout << "2\n";
        return 0;
    }


    return 0;
}
