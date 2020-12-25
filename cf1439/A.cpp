#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e2;

int t;
int n,m;
string s[NMAX + 5];
queue<int> q;
int ant[1 << 4];


vector<pair<int,int> > ans;
void flip(int i,int j){
    s[i][j] = ((s[i][j] - '0') ^ 1) + '0';
    ans.push_back({i,j});
}

void solve2x2(){
    int nod = 8 * (s[n - 1][m - 1] == '1') + 4 * (s[n - 1][m] == '1') + 2 * (s[n][m - 1] == '1') + (s[n][m] == '1');

    while(nod){
        int conf = (ant[nod] ^ nod);

        if(conf & (1 << 3)){
            flip(n - 1,m - 1);
        }
        if(conf & (1 << 2)){
            flip(n - 1,m);
        }
        if(conf & (1 << 1)){
            flip(n,m - 1);
        }
        if(conf & (1 << 0)){
            flip(n,m);
        }
        nod = ant[nod];
    }
}

int main(){

    for(int i = 0;i < 16;i++){
        ant[i] = -2;
    }

    ant[0] = -1;
    q.push(0);

    while(q.empty() == false){
        int nod = q.front();
        q.pop();
        for(int i = 0;i < 4;i++){
            if(ant[nod ^ 15 ^ (1 << i)] == -2){
                ant[nod ^ 15 ^ (1 << i)] = nod;
                q.push(nod ^ 15 ^ (1 << i));
            }
        }
    }

    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    cin >> t;

    while(t--){
        ans.clear();
        cin >> n >> m;

        for(int i = 1;i <= n;i++){
            cin >> s[i];
            s[i] = " " + s[i];
        }

        for(int i = 1;i <= n - 2;i++){
            for(int j = 1;j <= m;j ++){
                if(s[i][j] == '1'){
                    flip(i,j);
                    flip(i + 1,j);
                    flip(i + 1,(j < m ? j + 1:j - 1));
                }
            }
        }

        for(int j = 1;j <= m - 2;j++){
            if(s[n - 1][j] == '0' && s[n][j] == '0'){
                continue;
            }
            else if(s[n - 1][j] == '0' && s[n][j] == '1'){
                flip(n,j);
                flip(n - 1,j + 1);
                flip(n,j + 1);
                continue;
            }
            else if(s[n - 1][j] == '1' && s[n][j] == '0'){
                flip(n - 1,j);
                flip(n - 1,j + 1);
                flip(n,j + 1);
                continue;
            }
            else{
                flip(n - 1,j);
                flip(n,j);
                flip(n - 1,j + 1);
                continue;
            }
        }

        solve2x2();

        printf("%d\n",(int)ans.size() / 3);
        for(int i = 0;i < (int)ans.size();i += 3){
            printf("%d %d %d %d %d %d\n",ans[i].first,ans[i].second,ans[i + 1].first,ans[i + 1].second,ans[i + 2].first,ans[i + 2].second);
        }
    }

    return 0;
}
