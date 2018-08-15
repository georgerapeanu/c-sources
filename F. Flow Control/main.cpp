#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;

int N,M;
int X[NMAX + 5],Y[NMAX + 5];
int S[NMAX + 5];
vector<pair<int,int> > G[NMAX + 5];
int Edge_Val[NMAX + 5];
bool viz[NMAX + 5];
int father[NMAX + 5];

void dfs(int nod,int tata){
    father[nod] = tata;
    viz[nod] = 1;
    for(auto it:G[nod]){
        if(!viz[it.first]){
            dfs(it.first,nod);
            Edge_Val[it.second] = S[it.first];
            S[nod] += S[it.first];
            S[it.first] = 0;
        }
    }
}

int main(){

    scanf("%d",&N);

    for(int i = 1;i <= N;i++){
        scanf("%d",&S[i]);
    }

    scanf("%d",&M);

    for(int i = 1;i <= M;i++){
        scanf("%d %d",&X[i],&Y[i]);
        G[X[i]].push_back({Y[i],i});
        G[Y[i]].push_back({X[i],i});
    }

    for(int i = 1;i <= N;i++){
        if(!viz[i]){
            dfs(i,0);
            if(S[i] != 0){
                printf("Impossible\n");
                return 0;
            }
        }
    }

    printf("Possible\n");
    for(int i = 1;i <= M;i++){
        if(Edge_Val[i] && Y[i] == father[X[i]]){
            Edge_Val[i] *= -1;
        }
        printf("%d\n",Edge_Val[i]);
    }

    return 0;
}
