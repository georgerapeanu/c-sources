#include <cstdio>
#include <algorithm>
#include <deque>
#include <queue>
using namespace std;
FILE *f = fopen("delfin.in","r");
FILE *g = fopen("delfin.out","w");
int N,M;
char C[1005][1005];
pair<int,int> S;
pair<int,int> D;
pair<int,int> P;
int PDists[1005][1005];
int SDists[1005][1005];
bool U[1005][1005];
const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};
deque<pair<int,int> > Q;
priority_queue<pair<int,pair<int,int> >,vector<pair<int,pair<int,int> > > ,greater<pair<int,pair<int,int> > > > H;
bool ok(int x,int y){
    return 1 <= x && x <= N && 1 <= y && y <= M;
}
int main(){
    fscanf(f,"%d %d\n",&N,&M);
    for(int i = 1;i <= N;i++){
        fgets(C[i] + 1,1005,f);
        for(int j = 1;j <= M;j++){
            if(C[i][j] == 'S'){
                S = {i,j};
            }
            else if(C[i][j] == 'F'){
                D = {i,j};
            }
            else if(C[i][j] == 'D'){
                P = {i,j};
            }
        }
    }
    ///stage 1 - finding S,P distances and first water layer
    PDists[P.first][P.second] = 1;
    Q.push_back(P);
    while(!Q.empty()){
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop_front();
        for(int k = 0;k < 4;k++){
            int xx = x + dx[k];
            int yy = y + dy[k];
            if(ok(xx,yy) && (C[xx][yy] == '0' || C[xx][yy] == 'D') && !PDists[xx][yy]){
                PDists[xx][yy] = 1 + PDists[x][y];
                Q.push_back({xx,yy});
            }
        }
    }
    Q.push_back(S);
    SDists[S.first][S.second] = 1;
    while(!Q.empty()){
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop_front();
        if(C[x][y] == '0' || C[x][y] == 'D'){
            continue;
        }
        for(int k = 0;k < 4;k++){
            int xx = x + dx[k];
            int yy = y + dy[k];
            if(ok(xx,yy) && !SDists[xx][yy]){
                SDists[xx][yy] = 1 + SDists[x][y];
                Q.push_back({xx,yy});
            }
        }
    }
    ///stage 2 - combining the water and earth distances
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            if((C[i][j] == '0' || C[i][j] == 'D') && SDists[i][j] && PDists[i][j]){
                SDists[i][j] = max(SDists[i][j],PDists[i][j]);
                H.push({SDists[i][j],{i,j}});
            }
        }
    }
    ///stage 3 - finding the water distances and first earth layer
    while(!H.empty()){
        int x = H.top().second.first;
        int y = H.top().second.second;
        int cost = H.top().first;
        H.pop();
        if(cost != SDists[x][y]){
            continue;
        }
        if(C[x][y] != '0' && C[x][y] != 'D'){
            U[x][y] = 1;
            continue;
        }
        for(int k = 0;k < 4;k++){
            int xx = x + dx[k];
            int yy = y + dy[k];
            if(ok(xx,yy) && (!SDists[xx][yy] || SDists[xx][yy] > 1 + SDists[x][y])){
                SDists[xx][yy] = 1 + SDists[x][y];
                H.push({SDists[xx][yy],{xx,yy}});
            }
        }
    }
    ///stage 4 - propagating the earth layer
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            if(U[i][j]){
                H.push({SDists[i][j],{i,j}});
            }
        }
    }
    while(!H.empty()){
        int x = H.top().second.first;
        int y = H.top().second.second;
        int cost = H.top().first;
        H.pop();
        if(cost != SDists[x][y]){
            continue;
        }
        for(int k = 0;k < 4;k++){
            int xx = x + dx[k];
            int yy = y + dy[k];
            if(ok(xx,yy) && (!SDists[xx][yy] || SDists[xx][yy] > SDists[x][y] + 1) && C[xx][yy] != '0' && C[xx][yy] != 'D'){
                SDists[xx][yy] = 1 + SDists[x][y];
                H.push({SDists[xx][yy],{xx,yy}});
            }
        }
    }
    fprintf(g,"%d",SDists[D.first][D.second] - 1);
    fclose(f);
    fclose(g);
    return 0;
}
