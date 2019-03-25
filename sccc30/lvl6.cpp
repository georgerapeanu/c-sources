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

    bool operator < (const color_t &other)const {
        if(r != other.r) return r < other.r;
        if(g != other.g) return g < other.g;
        return b < other.b;

    }

    color_t merge(color_t &other){
        color_t ans = *this;
        ans.r += other.r;
        ans.b += other.b;
        ans.g += other.g;
        ans.r /= 2;
        ans.b /= 2;
        ans.g /= 2;
        return ans;
    }
};

int n,m;
int x,y;
int k;

vector<vector<color_t> > v;

int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

struct state_t{
    long long cost;
    color_t color;
    int x,y;

    bool operator < (const state_t &other)const{
        if(cost != other.cost)return cost > other.cost;
        if(color < other.color ||  other.color < color) return color < other.color;
        if(x != other.x) return x < other.x;
        return y < other.y;
    }

};

struct viz_t{
    color_t color;
    int x,y;
    bool operator < (const viz_t &other)const{
        if(color < other.color || other.color < color){
            return color < other.color;
        }
        if(x != other.x){
            return x < other.x;
        }
        return y < other.y;
    }
};

map<viz_t ,long long> viz;

long long solve(int x,int y,int xx,int yy,color_t rob_color){
    
    viz[{rob_color,x,y}] = 0;
    priority_queue<state_t>pq;

    long long ans = 1LL << 60;;

    pq.push({0,rob_color,x,y});

    while(!pq.empty()){
        int x = pq.top().x;
        int y = pq.top().y;
        rob_color = pq.top().color;
        long long cost = pq.top().cost;

        pq.pop();

        if(cost != viz[{rob_color,x,y}]){
            continue;
        }

        if(x == xx && y == yy){
            ans = min(ans,cost);
        }

        for(int k = 0;k < 4;k++){
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx <= 0 || nx > n || ny <= 0 || ny > m){
                continue;
            }

            if(v[nx][ny].r + v[nx][ny].b + v[nx][ny].g == 0){
                continue;
            }

            color_t n_color = rob_color.merge(v[nx][ny]);

            if(viz.count({n_color,nx,ny}) == 0 || viz[{n_color,nx,ny}] > cost + rob_color.round_dist(v[nx][ny]) + 1){
                viz[{n_color,nx,ny}] = cost + rob_color.round_dist(v[nx][ny]) + 1;
                pq.push({viz[{n_color,nx,ny}],n_color,nx,ny});
            }
        }
    }

    return ans;
}

int main(){


    cin >> n >> m;
    cin >> k;

    v = vector<vector<color_t> >(n + 4,vector<color_t>(m + 4,{0,0,0}));
    vector<pair<int,int> > fst(k + 4);
    vector<pair<int,int> > snd(k + 4);

    vector<color_t> init(k + 5);

    for(int i = 1;i <= k;i++){
        cin >> fst[i].first >> fst[i].second;
        cin >> snd[i].first >> snd[i].second;
        cin >> init[i].r >> init[i].g >> init[i].b;
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
        printf("%lld\n",solve(fst[i].first,fst[i].second,snd[i].first,snd[i].second,init[i]));
    }
    

    return 0;
}
