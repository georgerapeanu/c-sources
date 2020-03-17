#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

FILE *f = fopen("volum.in","r");
FILE *g = fopen("volum.out","w");

const int NMAX = 800;

int n,m;

int v[NMAX + 5][NMAX + 5];
int h[NMAX + 5][NMAX + 5];

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

int main(){

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            fscanf(f,"%d",&v[i][j]);
            h[i][j] = -1;
        }
    }

    priority_queue<pair<int,pair<int,int> >,vector<pair<int,pair<int,int> > >,greater<pair<int,pair<int,int> > > >pq;

    for(int i = 1;i <= n;i++){
        h[i][1] = v[i][1];
        h[i][m] = v[i][m];
        pq.push({h[i][1],{i,1}});
        pq.push({h[i][m],{i,m}});
    }

    for(int j = 1;j <= m;j++){
        h[1][j] = v[1][j];
        h[n][j] = v[n][j];
        pq.push({h[1][j],{1,j}});
        pq.push({h[n][j],{n,j}});
    }

    while(!pq.empty()){
        int cost = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        for(int k = 0;k < 4;k++){
            int xx = x + dx[k];
            int yy = y + dy[k];
            if(1 <= xx && xx <= n && 1 <= yy && yy <= m && h[xx][yy] == -1){
                h[xx][yy] = max(h[x][y],v[xx][yy]);
                pq.push({h[xx][yy],{xx,yy}});
            }
        }
    }

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            ans += (h[i][j] - v[i][j]);
        }
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
