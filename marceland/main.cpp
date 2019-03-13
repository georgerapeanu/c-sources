#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("marceland.in","r");
FILE *g = fopen("marceland.out","w");

const int TMAX = 5;
const int NMAX = 100;
const int MMAX = 100;

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};


int t;
int n,m;
char c[NMAX + 5][NMAX + 5];
bool viz[NMAX + 5][NMAX + 5];

pair<int,int> q[NMAX * NMAX + 5];
int st,dr;

int Solve(int i,int j){
    viz[i][j] = true;
    q[st = dr = 1] = {i,j};

    bool hasM = false;
    bool hasF = false;
    bool hasS = false;

    int sx = -1,sy = -1;

    while(st <= dr){
        int x = q[st].first;
        int y = q[st].second;
        st++;

        hasM |= (c[x][y] == 'M');
        hasF |= (c[x][y] == '@');
        if(c[x][y] == '.'){
            hasS = true;
            sx = x;
            sy = y;
        }

        for(int k = 0;k < 4;k++){
            int xx = x + dx[k];
            int yy = y + dy[k];
            if(xx <= 0 || xx > n || yy <= 0 || yy > m || viz[xx][yy] == true || c[xx][yy] == '#'){
                continue;
            }
            q[++dr] = {xx,yy};
            viz[xx][yy] = true;
        }
    }

    if(hasM == false){
        return 0;
    }

    if(hasF == true){
        return 0;
    }

    if(hasS == true){
        c[sx][sy] = '@';
        return 1;
    }

    return -1;
}

int main(){

    fscanf(f,"%d\n",&t);

    while(t--){
        fscanf(f,"%d %d\n",&n,&m);
        for(int i = 1;i <= n;i++){
            fgets(c[i] + 1,m + 5,f);
            for(int j = 1;j <= m;j++){
                viz[i][j] = false;
            }
        }

        int cnt = 0;
        bool ok = true;

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                if(c[i][j] != '#' && viz[i][j] == false){
                    int tmp = Solve(i,j);
                    cnt += tmp;
                    if(tmp == -1){
                        ok = false;
                    }
                }
            }
        }

        if(ok){
            fprintf(g,"%d\n",cnt);
            for(int i = 1;i <= n;i++){
                fputs(c[i] + 1,g);
            }
        }
        else{
            fprintf(g,"-1\n");
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
