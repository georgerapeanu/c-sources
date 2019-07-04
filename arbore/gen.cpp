#include <cstdio>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

FILE *g = fopen("arbore.in","w");

const int PMAX = 5e7;
const int NMAX = 1e5;
const int MMAX = 1e5;
const int SMAX = 10;
const int VMAX = 1e6;

int n,m;
vector<int> graph[NMAX + 5];
int val[NMAX + 5];
int father[NMAX + 5];

void dfs(int nod,int delta) {
    val[nod] += delta;

    for(auto it:graph[nod]) {
        if(it == father[nod]) {
            continue;
        }
        dfs(it,delta);
    }
}

int main() {

    random_device rd;
    mt19937 gen(rd());

    n = gen() % NMAX + 1;
    m = (gen() % 2 ? min(MMAX,(PMAX / n)) : (gen() % min(MMAX,PMAX / n) + 1));

    fprintf(g,"%d %d\n",n,m);

    for(int i = 2; i <= n; i++) {
        int u = i;
        int v = gen() % (i - 1) + 1;

        fprintf(g,"%d %d\n",u,v);
        father[v] = u;
    }

    while(m--) {
        if(gen() & 1) {
            int p,s;
            p = gen() % n + 1;
            s = gen() % SMAX + 1;
            fprintf(g,"1 %d %d\n",p,s);
            dfs(p,s);
        }
        else {
            int pos = gen() % (n + 1) + 1;
            int tmp;
            if(pos == n + 1) {
                tmp = gen() % VMAX + 1;
            }
            else {
                tmp = val[pos];
            }
            fprintf(g,"2 %d\n",tmp);
        }
    }


    fclose(g);

    return 0;
}
