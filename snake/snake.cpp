#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("snake.in","r");
FILE *g = fopen("snake.out","w");

const int NMAX = 100;

int n,m,l;
int v[NMAX + 5][NMAX + 5];
pair<int,int> pos[NMAX * NMAX + 5];

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};
const int dx2[] = {-1,1,1,-1};
const int dy2[] = {1,1,-1,-1};

int lvl[NMAX + 5][NMAX + 5];
bool on_cycle[NMAX + 5][NMAX + 5];
vector<pair<int,int> > dfs_stack;


void predfs(pair<int,int> nod,pair<int,int> tata){
    lvl[nod.first][nod.second] = lvl[tata.first][tata.second] + 1;
    dfs_stack.push_back(nod);

    vector<int> neighbors;

    for(int k = 0;k < 4;k++){
        int xx = nod.first + dx[k];
        int yy = nod.second + dy[k];
        if(1 <= xx && xx <= n && 1 <= yy && yy <= m){
            neighbors.push_back(v[xx][yy]);
        }else{
            neighbors.push_back(-1);
        }
    }

    for(int k = 0;k < 4;k++){
        int a = neighbors[k];
        int b = neighbors[(k + 1) % 4];
        int xx = nod.first + dx2[k];
        int yy = nod.second + dy2[k];
        pair<int,int> to = {xx,yy};

        if(to == tata || xx < 1 || xx > n || yy < 1 || yy > m || a <= 0 || b <= 0 || abs(a - b) != 2){
            continue;
        }

        if(lvl[xx][yy]){
            if(lvl[xx][yy] > lvl[nod.first][nod.second]){
                continue;
            }
            for(int i = (int)dfs_stack.size() - 1;dfs_stack[i] != to;i--){
                on_cycle[dfs_stack[i].first][dfs_stack[i].second] = true;
            }
            on_cycle[to.first][to.second] = true;
        }else{
            predfs(to,nod);
        }
    }
    

    dfs_stack.pop_back();
}

void dfs(pair<int,int> nod){
    vector<int> neighbors;

    for(int k = 0;k < 4;k++){
        int xx = nod.first + dx[k];
        int yy = nod.second + dy[k];
        if(1 <= xx && xx <= n && 1 <= yy && yy <= m){
            neighbors.push_back(v[xx][yy]);
        }else{
            neighbors.push_back(-1);
        }
    }

    for(int k = 0;k < 4;k++){
        int a = neighbors[k];
        int b = neighbors[(k + 1) % 4];
        int xx = nod.first + dx2[k];
        int yy = nod.second + dy2[k];
        if(1 <= xx && xx <= n && 1 <= yy && yy <= m && a > 0 && b > 0 && abs(a - b) == 2 && v[xx][yy] == 0 && pos[(a + b) / 2] == make_pair(0,0)){
            pos[(a + b) / 2] = {xx,yy};
            v[xx][yy] = (a + b) / 2;
            dfs({xx,yy});
        }
    }
}

const int LEN = 1 << 20;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    int sgn = 1;

    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    if(buff[ind] == '-'){
        sgn *= -1;
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }


    while(buff[ind] >= '0' && buff[ind] <= '9'){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    return ans * sgn;
}


int main(){

    n = i32();
    m = i32();
    l = i32();

    vector<pair<int,int> > to_dfs;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            v[i][j] = i32();
            if(v[i][j] >= 0){
                pos[v[i][j]] = {i,j};
            }
            if(v[i][j] == -1){
                to_dfs.push_back({i,j});
            }
        }
    }

    for(int i = 2;i <= l;i += 2){
        if(pos[i - 1].first == pos[i + 1].first || pos[i - 1].second == pos[i + 1].second){
            pos[i].first = (pos[i - 1].first + pos[i + 1].first) / 2;
            pos[i].second = (pos[i - 1].second + pos[i + 1].second) / 2;
            v[pos[i].first][pos[i].second] = i;
            to_dfs.push_back(pos[i]);
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(lvl[i][j] == 0){
                predfs(make_pair(i,j),make_pair(0,0));
            }
            if(on_cycle[i][j]){
                to_dfs.push_back({i,j});
            }
        }
    }

    for(auto it:to_dfs){
        dfs(it);
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(v[i][j] == 0){
                dfs({i,j});
            }
        }
    }

    for(int i = 1;i <= l;i++){
        assert(pos[i] != make_pair(0,0));
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            fprintf(g,"%d ",v[i][j]);
        }
        fprintf(g,"\n");
    }

    fclose(f);
    fclose(g);

    return 0;
}
