#define JUDGE
#include <cstdio>
#include <queue>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("grea.in","r");
FILE *g = fopen("grea.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 25e4;

int n,k;
char c[2][NMAX + 5];
int d[2][NMAX + 5];
int link[2][NMAX + 5];

struct state_t {
    int x,y;
};

int main() {

    fscanf(f,"%d %d\n",&n,&k);

    fgets(c[0] + 1,NMAX + 2,f);
    fgets(c[1] + 1,NMAX + 2,f);

    int ind1 = n,ind2 = n;

    for(int i = n; i; i--) {

        while(ind1 && (i + k < ind1 || c[0][ind1] == '1')) {
            ind1--;
        }

        while(ind2 && (i + k < ind2 || c[1][ind2] == '1')) {
            ind2--;
        }

        if(ind1) {
            link[1][i] = ind1;
        }
        if(ind2) {
            link[0][i] = ind2;
        }

        d[0][i] = d[1][i] = NMAX * 5;
    }

    printf("\n");

    d[0][1] = 0;

    queue<state_t> q;

    q.push({0,1});

    while(!q.empty()) {
        state_t tmp = q.front();
        q.pop();

        if(tmp.y != 1 && d[tmp.x][tmp.y - 1] == NMAX * 5 && c[tmp.x][tmp.y - 1] == '0') {
            d[tmp.x][tmp.y - 1] = d[tmp.x][tmp.y] + 1;
            q.push({tmp.x,tmp.y - 1});
        }

        if(tmp.y != n && d[tmp.x][tmp.y + 1] == NMAX * 5 && c[tmp.x][tmp.y + 1] == '0') {
            d[tmp.x][tmp.y + 1] = d[tmp.x][tmp.y] + 1;
            q.push({tmp.x,tmp.y + 1});
        }

        if(link[tmp.x][tmp.y] && d[!tmp.x][link[tmp.x][tmp.y]] == NMAX * 5 && c[!tmp.x][link[tmp.x][tmp.y]] == '0') {
            d[!tmp.x][link[tmp.x][tmp.y]] = d[tmp.x][tmp.y] + 1;
            q.push({!tmp.x,link[tmp.x][tmp.y]});
        }
    }

    fprintf(g,"%d",min(d[0][n],d[1][n]));

    return 0;
}
