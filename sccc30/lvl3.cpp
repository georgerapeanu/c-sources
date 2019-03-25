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

vector<vector<color_t> > v;
vector<vector<int> > viz;

int dx[] = {-1,0,1};
int dy[] = {0,1,0};

int main(){


    cin >> n >> m;
    cin >> x >> y;
    x++;
    y++;

    v = vector<vector<color_t> >(n + 4,vector<color_t>(m + 4,{0,0,0}));
    viz = vector<vector<int> >(n + 4,vector<int>(m + 4,0));
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> v[i][j].r >> v[i][j].g >> v[i][j].b;
        }
    }

    viz[x][y] = true;

    while(true){
        printf("%d %d\n",x - 1,y - 1);

        int bestx = -1,besty = -1;

        for(int k = 0;k < 3;k++){
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx <= n && ny <= m && nx > 0 && ny > 0 && !viz[nx][ny] && (bestx == -1 || v[x][y].round_dist(v[bestx][besty]) > v[x][y].round_dist(v[nx][ny]))){
                bestx = nx;
                besty = ny;        
            }
        }

        if(bestx == -1){
            break;
        }
        
        x = bestx;
        y = besty;
        viz[bestx][besty] = true;
    }



    return 0;
}
