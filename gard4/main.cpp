#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
FILE *f = fopen("gard4.in","r");
FILE *g = fopen("gard4.out","w");
vector<int> L[40];
int V[40][40];
int N;
int last,rez = 1 << 30;
int D[40][40][1 << 5];
int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,1,1,1,0,-1,-1,-1};
int X[10];
int Y[10];
struct data{
    int x,y,mask,cost;
    bool operator < (const data &other)const{
        return cost > other.cost;
    }
};
priority_queue<data> H;
int dijkstra(int i,int j){
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            for(int k = 0;k < (1 << last);k++){
                D[i][j][k] = 1 << 28;
            }
        }
    }
    D[i][j][0] = 0;
    H.push({i,j,0,0});
    while(!H.empty()){
        data tmp = H.top();H.pop();
        if(D[tmp.x][tmp.y][tmp.mask] < tmp.cost){
            continue;
        }
        for(int k = 0;k < 8;k++){
            data to;
            to.x = tmp.x + dx[k];
            to.y = tmp.y + dy[k];
            if(to.x && to.y && to.x <= N && to.y <= N && V[to.x][to.y] != -1){
                to.cost = tmp.cost + V[tmp.x][tmp.y];
                to.mask = tmp.mask;
                if(to.x > tmp.x){
                    for(auto it:L[tmp.x]){
                        if(Y[it] >= tmp.y){
                            to.mask ^= (1 << it);
                        }
                    }
                }
                else if(to.x < tmp.x){
                    for(auto it:L[to.x]){
                        if(Y[it] >= to.y){
                            to.mask ^= (1 << it);
                        }
                    }
                }
                if(D[to.x][to.y][to.mask] > to.cost){
                    D[to.x][to.y][to.mask] = to.cost;
                    H.push(to);
                }
            }
        }
    }
    return D[i][j][(1 << last) - 1];
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            fscanf(f,"%d",&V[i][j]);
            if(V[i][j] == -1){
                X[last] = i;
                Y[last] = j;
                L[i].push_back(last++);
            }
        }
    }
    for(int i = 1;i <= N;i++){
        if(L[i].size()){
            for(int j = 1;V[i][j] != -1;j++){
                rez = min(rez,dijkstra(i,j));
            }
            break;
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
