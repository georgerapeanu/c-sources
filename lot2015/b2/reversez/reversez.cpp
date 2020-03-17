#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("reversez.in","r");
FILE *g = fopen("reversez.out","w");

const int NMAX = 3e5;
const int SMAX = 1e5;

int n,s;
int v[NMAX  + 5];

const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

vector<int> graph[2][NMAX + 5];
int comp[NMAX + 5],lst_comp;
int gr[NMAX + 5];

void dfs(int nod,int col) {
    comp[nod] = col;
    for(auto it:graph[0][nod]) {
        if(comp[it] == 0) {
            dfs(it,col);
        }
    }
}

int main() {

    n = i32();
    s = i32();

    for(int i = 1; i <= n; i++) {
        v[i] = i32();
    }

    int lst = 1;

    for(int i = 2; i <= n; i++) {
        lst = max(lst,i);
        while(lst < i + v[i]) {
            graph[0][lst].push_back(lst - i + 1);
            graph[0][lst - i + 1].push_back(lst);
            lst++;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(comp[i] == 0) {
            dfs(i,++lst_comp);
        }
    }

    for(int i = 1; i <= n; i++) {
        if(i + v[i] <= n) {
            graph[1][comp[v[i] + 1]].push_back(comp[i + v[i]]);
            graph[1][comp[i + v[i]]].push_back(comp[v[i] + 1]);
        }
    }

    int ans = 1;

    for(int i = 1; i <= lst_comp; i++) {
        sort(graph[1][i].begin(),graph[1][i].end());
        graph[1][i].resize(unique(graph[1][i].begin(),graph[1][i].end()) - graph[1][i].begin());

        ans = 1LL * ans * (s - gr[i]) % 666013;

        for(auto it:graph[1][i]) {
            gr[it]++;
        }
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
