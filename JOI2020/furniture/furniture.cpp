#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,int> > fst,snd;

int n,m;
int dp[1005][1005];

void update(int x,int y){
    if(x <= 0 || y <= 0){
        return ;
    }
    dp[x][y] = 0;
    if(dp[x - 1][y]){
        dp[x - 1][y]--;
        if(dp[x - 1][y] == 0){
            update(x - 1,y);
        }
    }
    if(dp[x][y - 1]){
        dp[x][y - 1]--;
        if(dp[x][y - 1] == 0){
            update(x,y - 1);
        }
    }
}

void refresh(vector<pair<int,int> > &v,int pos,int dir){
    if(dp[v[pos].first][v[pos].second] > 0){
        return ;
    }
    while(dp[v[pos].first][v[pos].second] == 0){
        pos--;
    }
    while(true){
        if(dp[v[pos].first + dir][v[pos].second + 1 - dir] > 0){
            pair<int,int> tmp = {v[pos].first + dir,v[pos].second + 1 - dir};   
            if(v[pos + 1] == tmp){
                break;
            }
            v[pos + 1] = tmp;
        }
        else{
            pair<int,int> tmp = {v[pos].first + 1 - dir,v[pos].second + dir};   
            if(v[pos + 1] == tmp){
                break;
            }
            v[pos + 1] = tmp;
        }
        pos++;
    }
}

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            scanf("%d",&dp[i][j]);
            dp[i][j] ^= 1;
        }
    }

    dp[n][m] = 1;

    for(int i = n;i;i--){
        for(int j = m;j;j--){
            if(i == n && j == m){
                continue;
            }
            if(dp[i][j] == 1){
                dp[i][j] = (dp[i + 1][j] > 0) + (dp[i][j + 1] > 0);
            }
        }
    }

    fst = {{1,1}};
    snd = {{1,1}};

    for(int i = 2;i < n + m;i++){
        if(dp[fst.back().first][fst.back().second + 1]){
            fst.push_back({fst.back().first,fst.back().second + 1});
        }
        else{
            fst.push_back({fst.back().first + 1,fst.back().second});
        }
        if(dp[snd.back().first + 1][snd.back().second]){
            snd.push_back({snd.back().first + 1,snd.back().second});
        }
        else{
            snd.push_back({snd.back().first,snd.back().second + 1});
        }
    }

    int q;

    scanf("%d",&q);

    while(q--){
        int x,y;
        scanf("%d %d",&x,&y);
        /* 
        for(auto it:fst)printf("(%d %d), ",it.first,it.second);printf("\n");
        for(auto it:snd)printf("(%d %d), ",it.first,it.second);printf("\n");
        printf("\n");
        */
        if(fst[x + y - 2] != make_pair(x,y) || snd[x + y - 2] != make_pair(x,y)){
            printf("1\n");
            if(dp[x][y] > 0){
                update(x,y);
            }
            if(dp[1][1] == 0){
                while(true);
            }
            refresh(fst,x + y - 2,0);
            refresh(snd,x + y - 2,1);
        }
        else{
            printf("0\n");
        }

    }

    return 0;
}
