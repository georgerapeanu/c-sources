#include <bits/stdc++.h>

using namespace std;

ifstream f("partmin.in");
ofstream g("partmin.out");

const int NMAX = 1e3;
const int KMAX = 1e3;

int n,k;
string s;
string tmp;

int d[NMAX + 5][NMAX + 5];
int manacher[2 * NMAX + 5];
int dp[2][NMAX + 5];

void solve(int st,int dr,int l,int r){
    if(st > dr){
        return ;
    }

    int mid = (st + dr) / 2;
    int bst = -1;

    for(int j = l;j <= r && j < mid;j++){
        if(dp[1][mid] > dp[0][j] + d[j + 1][mid]){
            bst = j;
            dp[1][mid] = dp[0][j] + d[j + 1][mid];
        }
    }

    solve(st,mid - 1,l,bst);
    solve(mid + 1,dr,bst,r);
}

int main(){

    f >> n >> k;
    f >> s;

    tmp = "#";

    for(auto it:s){
        tmp += it;
        tmp += "#";
    }
    swap(s,tmp);

    int best = -1;

    for(int i = 0;i < (int)s.size();i++){
        if(best != -1 && best + manacher[best] >= i){
            manacher[i] = min(manacher[2 * best - i],best + manacher[best] - i);
        }
        while(i - manacher[i] >= 0 && i + manacher[i] < (int)s.size() && s[i - manacher[i]] == s[i + manacher[i]]){
            manacher[i]++;
        }
        manacher[i]--;
        if(best == -1 || i + manacher[i] > best + manacher[best]){
            best = i;
        }
    }

    for(int i = 1;i < (int)s.size();i += 2){
        for(int j = i;j < (int)s.size();j++){
            int _length = min(j - i,manacher[j]);
            int l = 0;
            int r = 0;
            
            l = j / 2 + 1;
            if((j + _length) & 1){
                r = (j + _length) / 2 + 1;
            }else{
                r = (j + _length) / 2;
            }
            if(l <= r){
                d[i / 2 + 1][l]++;
                if(r + 1 <= n){
                    d[i / 2 + 1][r + 1]--;
                }
            }
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            d[i][j] += d[i][j - 1];
        }
        for(int j = 1;j <= n;j++){
            d[i][j] += d[i][j - 1];
        }
    }

    for(int i = 1;i <= n;i++){
        dp[1][i] = d[1][i];
    }
    if(k > 0){
        g << dp[1][n] << "\n";
    }

    for(int h = 2;h <= k;h++){
        for(int i = 1;i <= n;i++){
            dp[0][i] = dp[1][i];
            dp[1][i] = 1e9;
        }
        solve(1,n,0,n - 1);
        g << dp[1][n] << "\n";
    }


    f.close();
    g.close();

    return 0;
}
