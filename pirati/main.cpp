#include <cstdio>
#include <vector>
using namespace std;
FILE *f = fopen("pirati.in","r");
FILE *g = fopen("pirati.out","w");
const int MaxNodes = 1000 * 1000 / 2;
const int LGMAX = 19;
const int NMAX = 1000;
const int dx[] = {-1,-1,0,1,1,1,0,-1};
const int dy[] = {0,1,1,1,0,-1,-1,-1};
int T[LGMAX + 1][MaxNodes + 1];
int lvl[MaxNodes + 1];
char C[NMAX + 5][NMAX + 5];
int N,M,Q;
pair<int,int> Qu[NMAX * NMAX + 5];
int V[NMAX + 5][NMAX + 5];
int stq,drq;
int new_val = 1;
void Fill(int x,int y){
    vector<pair<int,int> > vecini;
    stq = 1;drq = 0;
    Qu[++drq] = {x,y};
    int val = C[x][y] - '0';
    V[x][y] = new_val;
    while(stq <= drq){
        int x = Qu[stq].first;
        int y = Qu[stq].second;
        stq++;
        for(int k = 0;k < 8;k++){
            int xx = x + dx[k];
            int yy = y + dy[k];
            if(xx && yy && xx <= N && yy <= M && !V[xx][yy]){
                if(C[xx][yy] == '0' + val){
                    V[xx][yy] = new_val;
                    Qu[++drq] = {xx,yy};
                }
                else{
                    vecini.push_back({xx,yy});
                }
            }
        }
    }
    for(auto it:vecini){
        if(!V[it.first][it.second]){
            new_val++;
            T[0][new_val] = V[x][y];
            lvl[new_val] = 1 + lvl[V[x][y]];
            Fill(it.first,it.second);
        }
    }
}
void prelca(){
    for(int lg = 1;lg <= LGMAX;lg++){
        for(int i = 1;i <= new_val;i++){
            T[lg][i] = T[lg - 1][T[lg - 1][i]];
        }
    }
}
int lca(int x,int y){
    if(lvl[x] > lvl[y]){
        swap(x,y);
    }
    int dif = lvl[y] - lvl[x];
    for(int lg = LGMAX;lg >= 0;lg--){
        if((dif >> lg) & 1){
            y = T[lg][y];
        }
    }
    if(x == y){
        return x;
    }
    for(int lg = LGMAX;lg >= 0;lg--){
        if(T[lg][x] != T[lg][y]){
            x = T[lg][x];
            y = T[lg][y];
        }
    }
    return T[0][x];
}
int main(){
    fscanf(f,"%d %d %d\n",&N,&M,&Q);
    for(int i = 1;i <= N;i++){
        fgets(C[i] + 1,1005,f);
    }
    lvl[1] = 1;
    Fill(1,1);
    prelca();
    while(Q--){
        int x,xx,y,yy;
        fscanf(f,"%d %d %d %d",&x,&y,&xx,&yy);
        fprintf(g,"%d\n",(lvl[V[x][y]] + lvl[V[xx][yy]] - 2 * lvl[lca(V[x][y],V[xx][yy])]) / 2);
    }
    fclose(f);
    fclose(g);
    return 0;
}
