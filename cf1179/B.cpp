#include <bits/stdc++.h>

using namespace std;

const int PMAX = 1e6;

int n,m;
vector<vector<bool> > used;
vector<vector<bool> > viz;
vector<pair<int,int> > cells;

void btr(int x,int y) {
    cells.push_back({x,y});
    if((int)cells.size() == n * m) {
        for(auto it:cells) {
            printf("%d %d\n",it.first,it.second);
        }
        exit(0);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(viz[i][j] == false && used[n + (i - x)][m + (j - y)] == false) {
                viz[i][j] = true;
                used[n + (i - x)][m + (j - y)] = true;
                btr(i,j);
                viz[i][j] = false;
                used[n + (i - x)][m + (j - y)] = false;
            }
        }
    }
    cells.pop_back();
}

int p1d[PMAX + 5];

int main() {

    scanf("%d %d",&n,&m);

    int last = 0;

    for(int st = 1,dr = m; st != dr;) {
        last++;
        p1d[last] = dr - st;
        st += (dr > st ? 1:-1);
        swap(st,dr);
    }

    int rw = 1;
    int cl = 1;

    printf("1 1\n");

    for(int st = 1,dr = n; st <= dr; st++,dr--) {
        int deltax = dr - st;
        for(int i = 1; i < m; i++) {
            rw += deltax;
            cl += p1d[i];
            printf("%d %d\n",rw,cl);
            deltax *= -1;
        }
        if(st == dr) {
            continue;
        }
        rw += deltax;
        cl += 0;
        printf("%d %d\n",rw,cl);
        deltax *= -1;
        for(int i = m - 1; i >= 1; i--) {
            cl += -p1d[i];
            rw += deltax;
            printf("%d %d\n",rw,cl);
            deltax *= -1;
        }

        if(st == dr - 1) {
            continue;
        }

        if(rw == st) {
            rw += dr - 1 - st;
            cl += 1 - cl;
            printf("%d %d\n",rw,cl);
        }
        else {
            rw += st + 1 - dr;
            cl += 1 - cl;
            printf("%d %d\n",rw,cl);
        }
    }

    return 0;
}
