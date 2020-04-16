///vad ca mare maestru la feudal age e bunicu asta
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("freakadebunic.in","r");
FILE *g = fopen("freakadebunic.out","w");

const int NMAX = 1e5;

int k,n;
int weight[NMAX + 5];

vector<int> graph[NMAX + 5];

vector<int> devreme;

void dfs(int nod,int tata) {
    int cnt = (weight[nod] > 0);
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
        weight[nod] += weight[it];
        cnt += (weight[it] != 0);
    }
    if(cnt > 1) {
        devreme.push_back(nod);
    }
}

int main() {

    fscanf(f,"%d %d",&n,&k);

    for(int i = 1; i <= k; i++) {
        int node;
        fscanf(f,"%d",&node);
        weight[node] = 1;
    }

    for(int i = 1; i < n; i++) {
        int u,v;
        fscanf(f,"%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,0);

    sort(devreme.begin(),devreme.end());

    fprintf(g,"%d\n",(int)devreme.size());

    for(auto it:devreme) {
        fprintf(g,"%d ",it);
    }

    fclose(f);
    fclose(g);

    return 0;
}
