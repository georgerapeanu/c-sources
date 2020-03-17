#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("tairos.in","r");
FILE *g = fopen("tairos.out","w");

const int NMAX = 100;
const int DMAX = 10000;
const int MOD = 1e9 + 7;

int n;
int d;

vector<int> graph[NMAX + 5];
vector<int> leaf_lvls;
int fr[DMAX + 5];
int dp[DMAX + 5];

void dfs(int nod,int tata,int lvl = 0){
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod,lvl + 1);
    }
    if(nod != 1 && graph[nod].size() == (tata != 0)){
        leaf_lvls.push_back(lvl);
    }
    else{
        fr[lvl]++;
    }
}

int main(){

    fscanf(f,"%d %d",&n,&d);

    for(int i = 1;i < n;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);

    dp[0] = 1;

    for(int i = 1;i <= d;i++){
        for(auto it:leaf_lvls){
            if(i >= it){
                dp[i] += dp[i - it];
                if(dp[i] >= MOD){
                    dp[i] -= MOD;
                }
            }
        }
    }

    int ans = 0;

    for(int i = 0;i <= d;i++){
        ans = (ans + 1LL * dp[i] * fr[d - i]) % MOD;
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
