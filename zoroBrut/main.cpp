#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("zoro.in","r");
FILE *g = fopen("zoro.ok","w");
int V[1005][1005];
int bestDist[1005][1005];
int N,M;
int get(int x,int y){
    if(x == N && y == M){
        return bestDist[x][y] = 1;
    }
    if(!bestDist[x][y]){
        bestDist[x][y] = -(1 << 28);
        for(int c = 1;c <= M;c++){
            if(V[x][y] > V[x][c]){
                bestDist[x][y] = max(get(x,c) + 1,bestDist[x][y]);
            }
        }
        for(int l = 1;l <= N;l++){
            if(V[x][y] > V[l][y]){
                bestDist[x][y] = max(get(l,y) + 1,bestDist[x][y]);
            }
        }
    }
    return bestDist[x][y];
}
int main(){
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            fscanf(f,"%d",&V[i][j]);
        }
    }
    fprintf(g,"%d",get(1,1));
    fclose(f);
    fclose(g);
    return 0;
}
