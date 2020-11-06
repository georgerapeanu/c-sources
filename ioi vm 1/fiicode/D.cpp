#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct query_cell{
    int x,y,val;
    int st;
    int dr;
    int mid;
    bool activation;

    bool operator < (const query_cell &other){
        if(mid != other.mid){
            return mid > other.mid;
        }
        return activation > other.activation;
    }
};


int n,m;
pair<int,int> dsu[1005][1005];
int sz[1005][1005];
bool active[1005][1005];
int cnt[1000005];
int val[1005][1005];
int ans[1005][1005];
int maxi[1005][1005];

vector<pair<int,int> > stuff[1005][1005];

vector<pair<int,int> > cells[1000005];


const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

void reset(){
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            dsu[i][j] = {0,0};
            active[i][j] = 0;
            sz[i][j] = 0;
            stuff[i][j].clear();
            maxi[i][j] = 0;
        }
    }
}

pair<int,int> fi(pair<int,int> cell){
    if(dsu[cell.first][cell.second].first == 0){
        return cell;
    }

    return dsu[cell.first][cell.second] = fi(dsu[cell.first][cell.second]);
}

int get_val(pair<int,int> cell){
    return val[cell.first][cell.second];
}

bool unite(pair<int,int> x,pair<int,int> y,int val){
    x = fi(x);
    y = fi(y);

    if(x == y){
        return false;
    }

    dsu[x.first][x.second] = y;
    sz[y.first][y.second] += sz[x.first][x.second];
    maxi[y.first][y.second] = max(maxi[x.first][x.second],maxi[y.first][y.second]);
    
    while(stuff[x.first][x.second].size() && get_val(stuff[x.first][x.second].back()) < maxi[y.first][y.second]){
        ans[stuff[x.first][x.second].back().first][stuff[x.first][x.second].back().second] = val;
        stuff[x.first][x.second].pop_back();
    }

    while(stuff[y.first][y.second].size() && get_val(stuff[y.first][y.second].back()) < maxi[y.first][y.second]){
        ans[stuff[y.first][y.second].back().first][stuff[y.first][y.second].back().second] = val;
        stuff[y.first][y.second].pop_back();
    }

    if(stuff[y.first][y.second].size() < stuff[x.first][x.second].size()){
        swap(stuff[y.first][y.second],stuff[x.first][x.second]);
    }

    for(auto it:stuff[x.first][x.second]){
        stuff[y.first][y.second].push_back(it);
    }
    

    return true;
}

void activate(int x,int y){
    active[x][y] = true;
    stuff[x][y].push_back({x,y});
    sz[x][y] = 1;
    maxi[x][y] = val[x][y];

    for(int k = 0;k < 4;k++){
        int xx = x + dx[k];
        int yy = y + dy[k];
        if(xx >= 1 && xx <= n && yy >= 1 && yy <= m && active[xx][yy]){
            unite({x,y},{xx,yy},val[x][y]);
        }
    }
}

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            scanf("%d",&val[i][j]);
            cnt[val[i][j]]++;
            cells[val[i][j]].push_back({i,j});
        }
    }

    for(int i = 1e6;i >= 0;i--){
        cnt[i] += cnt[i + 1];
    }

    reset();

    for(int i = 1e6;i >= 0;i--){
        for(auto it:cells[i]){
            activate(it.first,it.second);
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(cnt[val[i][j] + 1] == 0){
                ans[i][j] = val[i][j];
            }
            else{
                ans[i][j] = val[i][j] - ans[i][j];
            }
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}

