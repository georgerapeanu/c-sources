#define JUDGE
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("avele.in","r");
FILE *g = fopen("avele.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 1e5;

int n,a,b;

vector<int> graph[NMAX + 5];

int lvl[NMAX + 5];
int weight[NMAX + 5];

long long ans;
void predfs(int nod,int tata,int height) {
    lvl[nod] = 1 + lvl[tata];
    weight[nod] = 1;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        predfs(it,nod,height);
    }
}

void dfs(int nod,int tata,int height) {
    if(lvl[nod] > height) {
        ans += 1LL * b * weight[nod];
        return ;
    }

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod,height);
    }

    if(graph[nod].empty()) {
        if(lvl[nod] >= height - 1) {
            return ;
        }
        ans += 1LL * a * ((1LL << (height - 1 - lvl[nod])) - 1);;
    }
}

int main() {

    fscanf(f,"%d %d %d",&n,&a,&b);

    for(int i = 1; i < n; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int height = 100;

    long long tmp_ans = 1LL << 60;

    while(height--) {
        ans = 0;
        dfs(1,0,height);
        tmp_ans = min(ans,tmp_ans);
    }

    fprintf(g,"%lld\n",ans);

    return 0;
}
