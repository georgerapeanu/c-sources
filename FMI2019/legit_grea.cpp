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

        unvis[0].insert(i);
        unvis[1].insert(i);
        d[0][i] = d[1][i] = NMAX * 5;
    }

    d[0][1] = 0;

    queue<state_t> q;

    q.push({0,1});

    unvis[0].erase(1);

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

        set<int> :: iterator it = unvis[!tmp.x].lower_bound(tmp.y - k);
        vector<int> to_erase;
        while(it != unvis[!tmp.x].end() && *it <= tmp.y + k) {
            d[!tmp.x][*it] = 1 + d[tmp.x][tmp.y];
            to_erase.push_back(*it);
            q.push({!tmp.x,*it});
            it++;
        }

        for(auto it:to_erase) {
            unvis[!tmp.x].erase(it);
        }
    }

    fprintf(g,"%d",min(d[0][n],d[1][n]));

    return 0;
}
