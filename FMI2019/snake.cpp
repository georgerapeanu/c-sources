#define JUDGE
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("snake.in","r");
FILE *g = fopen("snake.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 100;

struct state_t {
    int x,y;
};
state_t pos[NMAX * NMAX + 5];

int v[NMAX + 5][NMAX + 5];
int n,m,l;

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

bool force_take = false;

void Fill(int x,int y) {

    if(v[x][y] != 0) {
        return ;
    }

    vector<int> possible;

    for(int d1 = 0; d1 < 4; d1++) {
        if(!(x + dx[d1] > 0 && x + dx[d1] <= n && y + dy[d1] > 0 && y + dy[d1] <= m)) {
            continue;
        }
        int a = v[x + dx[d1]][y + dy[d1]];
        if(a == -1 || a % 2 == 0) {
            continue;
        }
        for(int d2 = d1 + 1; d2 < 4; d2++) {
            if(!(x + dx[d2] > 0 && x + dx[d2] <= n && y + dy[d2] > 0 && y + dy[d2] <= m)) {
                continue;
            }
            int b = v[x + dx[d2]][y + dy[d2]];
            if(b == -1 || b % 2 == 0) {
                continue;
            }

            if(a - b != 2 && b - a != 2) {
                continue;
            }
            if(pos[(a + b) / 2].x) {
                continue;
            }

            possible.push_back((a + b) / 2);
        }
    }

    if((int)possible.size() != 1 && force_take == false) {
        return;
    }

    if(possible.size() >= 1) {
        v[x][y] = possible[0];
        pos[possible[0]] = {x,y};
        force_take = false;
    }
    else {
        return;
    }

    Fill(x + 1,y + 1);
    Fill(x + 1,y - 1);
    Fill(x - 1,y + 1);
    Fill(x - 1,y - 1);
}


int main() {

    fscanf(f,"%d %d %d",&n,&m,&l);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fscanf(f,"%d",&v[i][j]);
            if(v[i][j] > 0) {
                pos[v[i][j]] = {i,j};
            }
        }
    }

    while(true) {

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                Fill(i,j);
            }
        }

        bool ok = true;

        for(int i = 1; i <= l; i += 1) {
            if(!pos[i].x) {
                ok = false;
            }
        }

        if(ok) {
            break;
        }

        force_take = true;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fprintf(g,"%d ",v[i][j]);
        }
        fprintf(g,"\n");
    }
    return 0;
}
