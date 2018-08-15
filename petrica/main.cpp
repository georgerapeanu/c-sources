#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("petrica.in","r");
FILE *g = fopen("petrica.out","w");

int N;
int V[205];
int W[205];
vector<int> G[205];

int FstSubtree,SndSubtree;
int best = 1 << 30;

void predfs(int nod,int tata){
    W[nod] = V[nod];
    for(auto it:G[nod]){
        if(it != tata){
            predfs(it,nod);
            W[nod] += W[it] * (it != FstSubtree && it != SndSubtree);
        }
    }
}

int MA,MI;

void dfs(int nod,int tata){
    best = min(best,max(MA,max(W[nod],W[1] - W[nod])) - min(MI,min(W[nod],W[1] - W[nod])));
    for(auto it:G[nod]){
        if(it != tata && it != FstSubtree && it != SndSubtree){
            dfs(it,nod);
        }
    }
}

int main(){
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
    }

    for(int i = 1;i < N;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for(int i = 2;i <= N;i++){
        for(int j = i + 1;j <= N;j++){
            FstSubtree = i;
            SndSubtree = j;
            predfs(1,0);
            if(W[1] < 2 || abs(V[i] - V[j]) >= best){
                continue;
            }
            MA = max(W[FstSubtree],W[SndSubtree]);
            MI = min(W[FstSubtree],W[SndSubtree]);
            dfs(1,0);
        }
    }

    fprintf(g,"%d",best);

    fclose(f);
    fclose(g);

    return 0;
}
