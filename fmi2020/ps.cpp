#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("ps.in","r");
FILE *g = fopen("ps.out","w");

const int NMAX = 2e5;

int n,m,k;

bool viz[NMAX + 5][2];
int who[NMAX + 5];
vector<int> graph[NMAX + 5][2];

int solve(int nod,int pos) {
    int cnt = (pos == 0 ? 1:-1);
    viz[nod][pos] = true;
    for(auto it:graph[nod][pos]) {
        if(viz[it][pos ^ 1] == 0) {
            if(pos == 0) {
                who[it] = nod;
            }
            cnt += solve(it,pos ^ 1);
        }
    }
    return cnt;
}

int main() {

    fscanf(f,"%d %d %d\n",&n,&m,&k);

    for(int i = 1; i <= k; i++) {
        int a,b;
        fscanf(f,"%d %d",&a,&b);
        graph[a][0].push_back(b);
        graph[b][1].push_back(a);
    }

    int bonus = 0;

    for(int i = 1; i <= n; i++) {
        if(viz[i][0] == 0 && graph[i][0].size() == 1) {
            bonus |= (solve(i,0) < 0);
        }
    }

    for(int i = 1; i <= n; i++) {
        if(viz[i][0] == 0) {
            bonus |=( solve(i,0) < 0);
        }
    }

    fprintf(g,"%d\n",bonus + 1);
    for(int i = 1; i <= m; i++) {
        fprintf(g,"%d ",who[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
