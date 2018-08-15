#include <cstdio>
#include <queue>
using namespace std;
FILE *f = fopen("biomech.in","r");
FILE *g = fopen("biomech.out","w");
const long long LIM = 1e18;
const int C = 21;
int change[8][8];
int Move[5][8];
int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,1,1,1,0,-1,-1,-1};
long long dist[40][2 * C + 1];
pair<int,int> ant[40][2 * C + 1];
void dijkstra(int st,int y){
    int x = st / 8;
    int orientation = st % 8;
    for(int i = 0; i < 40;i++){
        for(int j = 0;j < 2 * C + 1;j++){
            dist[i][j] = LIM;
        }
    }
    dist[x * 8 + orientation][y] = 0;
    priority_queue<pair<long long,pair<int,int> > , vector< pair<long long,pair<int,int> > > , greater< pair<long long,pair<int,int> > > > H;
    H.push({0,{x * 8 + orientation,y}});
    while(!H.empty()){
        int cost = H.top().first;
        int x = H.top().second.first / 8;
        int orient = H.top().second.first % 8;
        int y = H.top().second.second;
        H.pop();
        if(x * 8 + orient == 23 && y == 23){
            int a = 0;
        }
        if(cost != dist[x * 8 + orient][y]){
            continue;
        }
        for(int k = 0;k < 8;k++){
            if(dist[x * 8 + orient][y] + change[orient][k] < dist[x * 8 + k][y]){
                dist[x * 8 + k][y] = dist[x * 8 + orient][y] + change[orient][k];
                ant[x * 8 + k][y] = {x * 8 + orient,y};
                H.push({dist[x * 8 + k][y],{x * 8 + k,y}});
            }
        }
        int xx = x + dx[orient];
        int yy = y + dy[orient];
        if(xx >= 0 && xx < 5 && yy >= 0 && yy < 2 * C + 1){
            if(dist[xx * 8 + orient][yy] > dist[x * 8 + orient][y] + Move[x][orient]){
                dist[xx * 8 + orient][yy] = dist[x * 8 + orient][y] + Move[x][orient];
                ant[xx * 8 + orient][yy] = {x * 8 + orient,y};
                H.push({dist[xx * 8 + orient][yy],{xx * 8 + orient,yy}});
            }
        }
    }
}
struct matrix{
    long long A[40][40];
    matrix operator * (const matrix &other)const{
        matrix ans;
        for(int i = 0;i < 40;i++){
            for(int j = 0;j < 40;j++){
                ans.A[i][j] = LIM;
                for(int k = 0;k < 40;k++){
                    ans.A[i][j] = min(ans.A[i][j],A[i][k] + other.A[k][j]);
                }
            }
        }
        return ans;
    }
    long long getmin(){
        long long a = LIM;
        for(int i = 0;i < 40;i++){
            for(int j = 0;j < 40;j++){
                a = min(a,A[i][j]);
            }
        }
        return a;
    }
    void init(){
        for(int i = 0;i < 40;i++){
            for(int j = 0;j < 40;j++){
                A[i][j] = LIM;
            }
        }
        for(int i = 0;i < 8;i++){
            A[2 * 8 + i][2 * 8 + i] = 0;
        }
    }
}fwd[55],bwd[55];
long long T;
int main(){
    fscanf(f,"%lld",&T);
    for(int i = 0;i < 8;i++){
        for(int j = 0;j < 8;j++){
            fscanf(f,"%d",&change[i][j]);
        }
    }
    for(int i = 0;i < 5;i++){
        for(int j = 0;j < 8;j++){
            fscanf(f,"%d",&Move[i][j]);
        }
    }
    for(int i = 0;i < 40;i++){
        dijkstra(i,C);
        for(int j = 0;j < 40;j++){
            fwd[0].A[i][j] = dist[j][C + 1];
            bwd[0].A[i][j] = dist[j][C - 1];
        }
    }
    for(int i = 1;i < 55;i++){
        fwd[i] = fwd[i - 1] * fwd[i - 1];
        bwd[i] = bwd[i - 1] * bwd[i - 1];
    }
    matrix ultA,ultB;
    ultA.init();
    ultB.init();
    long long rez = 0;
    for(int pas = 52;pas >= 0;pas--){
        matrix tmpA = ultA * fwd[pas];
        matrix tmpB = ultB * bwd[pas];
        if(min(tmpA.getmin(),tmpB.getmin()) <= T){
            rez |= 1LL << pas;
            ultA = tmpA;
            ultB = tmpB;
        }
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
