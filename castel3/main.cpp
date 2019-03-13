#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("castel3.in","r");
FILE *g = fopen("castel3.out","w");

const int NMAX = 100;

int t;
int n;
int v[NMAX + 5][NMAX + 5];
bool viz[NMAX + 5][NMAX + 5];

int cnt;
int m_area = 0;
int ans_xst,ans_xdr,ans_yst,ans_ydr;
int xst,xdr,yst,ydr;

pair<int,int> q[NMAX * NMAX + 10];
int st,dr;

const int dx[] = {0,1,0,-1};
const int dy[] = {-1,0,1,0};

int Fill(int x,int y,int &xst,int &xdr,int &yst,int &ydr){
    xst = xdr = x;
    yst = ydr = y;

    q[st = dr = 1] = {x,y};
    viz[x][y] = true;

    int area = 0;

    while(st <= dr){
        x = q[st].first;
        y = q[st].second;

        if(y < yst || (y == yst && x < xst)){
            xst = x;
            yst = y;

        }

        if(y > ydr || (y == ydr && x > xdr)){
            xdr = x;
            ydr = y;
        }

        st++;
        area++;

        for(int k = 0;k < 4;k++){
            int xx = x + dx[k];
            int yy = y + dy[k];
            if(xx <= 0 || xx > n || yy <= 0 || yy > n){
                continue;
            }
            if(viz[xx][yy] || ((v[x][y] >> k) & 1) == 1){
                continue;
            }
            viz[xx][yy] = true;
            q[++dr] = {xx,yy};
        }
    }

    return area;
}

int main(){

    fscanf(f,"%d",&t);
    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            fscanf(f,"%d",&v[i][j]);
        }
    }

    Fill(1,1,xst,xdr,yst,ydr);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(viz[i][j] == false){
                cnt++;
                int tmp = Fill(i,j,xst,xdr,yst,ydr);
                if(tmp > m_area){
                    m_area = tmp;
                    ans_xst = xst;
                    ans_xdr = xdr;
                    ans_yst = yst;
                    ans_ydr = ydr;
                }
            }
        }
    }

    if(t == 1){
        fprintf(g,"%d\n",cnt);
    }
    else if(t == 2){
        fprintf(g,"%d\n",m_area);
    }
    else{
        fprintf(g,"%d %d %d %d\n",ans_xst,ans_yst,ans_xdr,ans_ydr);
    }

    fclose(f);
    fclose(g);

    return 0;
}
