#define JUDGE
#include <cstdio>
#include <queue>
#include <set>

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

set<int> unvis[2];

struct state_t {
    int x,y;
};

int main() {

    fscanf(f,"%d %d\n",&n,&k);

    fgets(c[0] + 1,NMAX + 2,f);
    fgets(c[1] + 1,NMAX + 2,f);

    for(int i = n; i; i--) {
        if(c[0][i] == '0') {
            unvis[0].insert(i);
        }
        if(c[1][i] == '0') {
            unvis[1].insert(i);
        }
        d[0][i] = d[1][i] = NMAX * 5;
    }

    d[0][1] = 0;

    queue<state_t> q;

    q.push({0,1});

    unvis[0].erase(1);

    while(!q.empty()) {
        state_t tmp = q.front();
        q.pop();

        if(tmp.y == n) {
            fprintf(g,"%d\n",d[tmp.x][tmp.y]);
            return 0;
        }

        if(unvis[tmp.x].count(tmp.y - 1)) {
            d[tmp.x][tmp.y - 1] = d[tmp.x][tmp.y] + 1;
            q.push({tmp.x,tmp.y - 1});
            unvis[tmp.x].erase(tmp.y - 1);
        }

        if(unvis[tmp.x].count(tmp.y + 1)) {
            d[tmp.x][tmp.y + 1] = d[tmp.x][tmp.y] + 1;
            q.push({tmp.x,tmp.y + 1});
            unvis[tmp.x].erase(tmp.y + 1);
        }

        set<int> :: iterator it = unvis[!tmp.x].lower_bound(tmp.y - k);
        while(it != unvis[!tmp.x].end() && *it <= tmp.y + k) {
            d[!tmp.x][*it] = 1 + d[tmp.x][tmp.y];
            q.push({!tmp.x,*it});
            it++;
            unvis[!tmp.x].erase(prev(it));
        }
    }
    return 0;
}
