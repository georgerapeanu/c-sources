#include <bits/stdc++.h>

using namespace std;

string s[10];
int dp[10][10];

int n,m;

int main(){

    cin >> n >> m;

    for(int i = 1;i <= n;i++){
        cin >> s[i];
        s[i] = " " + s[i];
    }

    for(int i = n;i >= 1;i--){
        for(int j = m;j >= 1;j--){
            pair<int,int> best = {i,j};
            for(int k = i;k <= n;k++){
                for(int l = j;l <= m;l++){
                    if(i == k && j == l){
                        continue;
                    }
                    if(s[k][l] == '.'){
                        continue;
                    }
                    if(best == make_pair(i,j) || best.first + best.second > k + l){
                        best = {k,l};
                    }
                }
            }
            dp[i][j] = (s[i][j] == '*') + dp[best.first][best.second];
        }
    }

    cout << dp[1][1];

    return 0;
}
