#include <bits/stdc++.h>

using namespace std;

struct color_t{
    int r,g,b;

    double dist(color_t &other){
        return sqrt((this -> r - other.r) * (this->r - other.r) +
                    (this->b - other.b) * (this->b - other.b) + 
                    (this->g - other.g) * (this->g - other.g)
                );
    }

    int round_dist(color_t &other){
        return (int)this->dist(other);
    }
};

int n,m;
int x,y;
int k;

vector<vector<color_t> > v;
vector<vector<int> > viz;

int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

int solve(int x,int y,int xx,int yy){
    viz = vector<vector<int> >(n + 4,vector<int>(m + 4,0));

    viz[x][y] = 1;
    queue<pair<int,int> > q;
    q.push({x,y});

    while(!q.empty()){
        x = q.front().first;
        y = q.front().second;
        q.pop();

        for(int k = 0;k < 4;k++){
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(0 < nx && nx <= n && 0 < ny && ny <= m && viz[nx][ny] == 0 && v[nx][ny].r + v[nx][ny].b + v[nx][ny].g > 0){
                q.push({nx,ny});
                viz[nx][ny] = viz[x][y] + 1;
            }
        }
    }

    return viz[xx][yy] - 1;
}

int main(){


    cin >> n >> m;
    cin >> k;

    v = vector<vector<color_t> >(n + 4,vector<color_t>(m + 4,{0,0,0}));
    viz = vector<vector<int> >(n + 4,vector<int>(m + 4,0));
    vector<pair<int,int> > fst(k + 4);
    vector<pair<int,int> > snd(k + 4);

    for(int i = 1;i <= k;i++){
        cin >> fst[i].first >> fst[i].second;
        cin >> snd[i].first >> snd[i].second;
        fst[i].first++;
        fst[i].second++;
        snd[i].first++;
        snd[i].second++;
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> v[i][j].r >> v[i][j].g >> v[i][j].b;
        }
    }

    for(int i = 1;i <= k;i++){
        printf("%d\n",solve(fst[i].first,fst[i].second,snd[i].first,snd[i].second));
    }


    return 0;
}
