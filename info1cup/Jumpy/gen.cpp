#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <queue>
#include <cassert>

using namespace std;

const int NMAX = 500;
const int MMAX = 500;
const int NMIN = NMAX * 0.9;
const int MMIN = MMAX * 0.9;

mt19937 gen;

void solve(int n,int m,int low_x,int high_x,int low_y,int high_y,vector<string> &ans,vector<int> &available_x,vector<int> &available_y){
    
    if(low_x + 1 >= high_x - 1 || low_y + 1 >= high_y - 1){
        for(int i = low_x;i < high_x;i++){
            for(int j = low_y;j < high_y;j++){
                ans[i][j] = '.';
            }
        }
        return ;
    }

    available_x.clear();
    available_y.clear();

    for(int i = low_x + 1;i < high_x - 1;i++){
        if((low_y == 0 || ans[i][low_y - 1] != '.') && (high_y == m || ans[i][high_y] != '.')){
            available_x.push_back(i);
        }
    }

    for(int i = low_y + 1;i < high_y - 1;i++){
        if((low_x == 0 || ans[low_x][i] != '.') && (high_x == n || ans[high_x][i] != '.')){
            available_y.push_back(i);
        }
    }

    if(available_x.empty() || available_y.empty()){
        for(int i = low_x;i < high_x;i++){
            for(int j = low_y;j < high_y;j++){
                ans[i][j] = '.';
            }
        }
        return ;
    }

    int l_x = available_x[int(gen() % (int)available_x.size())];
    int l_y = available_y[int(gen() % (int)available_y.size())];

    for(int i = low_y;i < high_y;i++){
        ans[l_x][i] = '#';
    }
    
    for(int i = low_x;i < high_x;i++){
        ans[i][l_y] = '#';
    }

    vector<pair<int,int> > free_cells;

    free_cells.push_back({l_x,gen() % (l_y - low_y) + low_y});
    free_cells.push_back({l_x,gen() % (high_y - l_y - 1) + l_y + 1});
    
    free_cells.push_back({gen() % (l_x - low_x) + low_x,l_y});
    free_cells.push_back({gen() % (high_x - l_x - 1) + l_x + 1,l_y});

    int banned_id = (gen() % (4 * 23 + 1)) / 23;

    for(int i = 0;i < (int)free_cells.size();i++){
        if(i != banned_id){
            ans[free_cells[i].first][free_cells[i].second] = '.';
        }
    }

    solve(n,m,low_x,l_x,low_y,l_y,ans,available_x,available_y);
    solve(n,m,l_x + 1,high_x,low_y,l_y,ans,available_x,available_y);
    solve(n,m,low_x,l_x,l_y + 1,high_y,ans,available_x,available_y);
    solve(n,m,l_x + 1,high_x,l_y + 1,high_y,ans,available_x,available_y);
}

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};
    
int n,m;

vector<string> ans;
int seen[NMAX][MMAX];
bool taken[NMAX][MMAX];
bool viz[NMAX][MMAX];

void assert_dfs(int x,int y,int f_x,int f_y){
    assert(0 <= x && x < n);
    assert(0 <= y && y < m);
    viz[x][y] = true;

    for(int k = 0;k < 4;k++){
        int xx = x + dx[k];
        int yy = y + dy[k];
        if((xx == f_x && yy == f_y) || xx < 0 || xx >= n || yy < 0 || yy >= m || ans[xx][yy] == '#'){
            continue;
        }
        assert(viz[xx][yy] == false);
        assert_dfs(xx,yy,x,y);
    }
}

int main(){

    gen = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    int subtask_id = -1;

    scanf("%d",&subtask_id);

    if(subtask_id == 1){
        /// n * m <= 20
        n = gen() % 5 + 1;
        m = gen() % (20 / n) + 1;
        assert(1 <= n);
        assert(1 <= m);
        assert(n * m <= 20);
    }else if(subtask_id == 2){
        ///empty
        n = gen() % (NMAX - NMIN + 1) + NMIN;
        m = gen() % (MMAX - MMIN + 1) + MMIN;
        assert(NMIN <= n && n <= NMAX);
        assert(MMIN <= m && m <= MMAX);
    }else if(subtask_id == 3){
        ///one is off
        n = gen() % (NMAX - NMIN + 1) + NMIN;
        m = gen() % (MMAX - MMIN + 1) + MMIN;
        assert(NMIN <= n && n <= NMAX);
        assert(MMIN <= m && m <= MMAX);
    }else if(subtask_id == 4){
        ///tree
        n = gen() % (NMAX - NMIN + 1) + NMIN;
        m = gen() % (MMAX - MMIN + 1) + MMIN;
        assert(NMIN <= n && n <= NMAX);
        assert(MMIN <= m && m <= MMAX);
    }else if(subtask_id == 5){
        ///1 <= n, m <= 300
        n = gen() % (300) + 1;
        m = gen() % (300) + 1;
        assert(1 <= n && n <= 300);
        assert(1 <= m && m <= 300);
    }else if(subtask_id == 6){
        ///general case
        n = gen() % (NMAX - NMIN + 1) + NMIN;
        m = gen() % (MMAX - MMIN + 1) + MMIN;
        assert(NMIN <= n && n <= NMAX);
        assert(MMIN <= m && m <= MMAX);
    }
    else{
        assert(false);
    }
    
    ans = vector<string>(n,string(m,' '));

    if(subtask_id == 1){
        vector<int> available_x;
        vector<int> available_y;

        solve(n,m,0,n,0,m,ans,available_x,available_y);
    }else if(subtask_id == 2){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                ans[i][j] = '.';
            }
        }
    }else if(subtask_id == 3){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                ans[i][j] = '.';
            }
        }
        int x,y;
        x = gen() % n;
        y = gen() % m;
        assert(0 <= x && x < n && 0 <= y && y < m);
        ans[x][y] = '#';
    }else if(subtask_id == 4){ 
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                ans[i][j] = '#';
            }
        }
        int x = gen() % n;
        int y = gen() % m;
        
        ans[x][y] = '.';
        priority_queue<pair<int,pair<int,int> > ,vector<pair<int,pair<int,int> > >,greater<pair<int,pair<int,int> > > > pq;
        pq.push({0,{x,y}});

        while(!pq.empty()){
            pair<int,pair<int,int> > stuff = pq.top();
            int cost = stuff.first;
            int x = stuff.second.first;
            int y = stuff.second.second;
            taken[x][y] = true;

            pq.pop();

            if(seen[x][y] > 1){
                continue;
            }

            ans[x][y] = '.';

            for(int k = 0;k < 4;k++){
                int xx = x + dx[k];
                int yy = y + dy[k];
                if(xx < 0 || xx >= n || yy < 0 || yy >= m || taken[xx][yy]){
                    continue;
                }
                if(seen[xx][yy] == 0){
                    pq.push({cost + (gen() % 100),{xx,yy}});
                }
                seen[xx][yy]++;
            }
        }

        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(viz[i][j] == false && ans[i][j] != '#'){
                    assert_dfs(i,j,-1,-1);
                }
            }
        }

    }else if(subtask_id == 5){
        vector<int> available_x;
        vector<int> available_y;

        solve(n,m,0,n,0,m,ans,available_x,available_y);
    }else if(subtask_id == 6){
        vector<int> available_x;
        vector<int> available_y;

        solve(n,m,0,n,0,m,ans,available_x,available_y);
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            assert(ans[i][j] == '.' || ans[i][j] == '#');
        }
    }

    cout << n << " " << m << "\n";
    for(int i = 0;i < n;i++){
        cout << ans[i] << "\n";
    }

    return 0;
}
