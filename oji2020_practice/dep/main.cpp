#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("dep.in","r");
FILE *g = fopen("dep.out","w");

const int NMAX = 256;
const int MOD = 666013;

int n,m,k;
vector<int> graph[NMAX + 5];
vector<int> tree[NMAX + 5];
vector<int> ctc[NMAX + 5];
int gr[NMAX + 5];

bool inst[NMAX + 5];
int id[NMAX + 5];
int low[NMAX + 5];
int st[NMAX + 5],len_st;

int lst_id;
int comp[NMAX + 5];
int weight[NMAX + 5];
int last_comp;

int dp[NMAX + 5][NMAX + 5];

void dfs(int nod){

    low[nod] = id[nod] = ++lst_id;
    inst[nod] = true;
    st[++len_st] = nod;

    for(auto it:graph[nod]){
        if(id[it] == 0){
            dfs(it);
            low[nod] = min(low[nod],low[it]);
        }
        else if(inst[it]){
            low[nod] = min(low[nod],low[it]);
        }
    }

    if(id[nod] == low[nod]){
        ++last_comp;
        while(st[len_st] != nod){
            comp[st[len_st]] = last_comp;
            inst[st[len_st]] = false;
            weight[last_comp] ++;
            len_st--;
        }
        comp[st[len_st]] = last_comp;
        weight[last_comp] ++;
        inst[st[len_st]] = false;
        len_st--;
    }
}

int tmp[NMAX + 5];

void solve(int nod){
    dp[nod][weight[nod]] = 1;
    for(auto it:tree[nod]){
        solve(it);
        for(int i = 0;i <= weight[nod] + weight[it] && i <= k;i++){
            tmp[i] = 0;
        }
        for(int i = weight[nod];i >= 0;i--){
            if(dp[nod][i] == 0){
                continue;
            }
            for(int j = min(weight[it],k - i);j >= 0;j--){
                if(dp[it][j] == 0){
                    continue;
                }
                tmp[i + j] = (tmp[i + j] + 1LL * dp[nod][i] * dp[it][j]) % MOD;
            }
        }
        weight[nod] += weight[it];
        weight[nod] = min(weight[nod],k);
        for(int i = 0;i <= weight[nod];i++){
            dp[nod][i] = tmp[i];
        }
    }

    dp[nod][0] = 1;
}

int main(){

    fscanf(f,"%d %d %d",&n,&m,&k);

    for(int i = 1;i <= m;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[y].push_back(x);
    }

    for(int i = 1;i <= n;i++){
        if(id[i] == 0){
            dfs(i);
        }
    }

    for(int i = 1;i <= n;i++){
        for(auto it:graph[i]){
            if(comp[it] != comp[i]){
                ctc[comp[i]].push_back(comp[it]);
            }
        }
    }

    for(int i = 1;i <= last_comp;i++){
        for(auto it:ctc[i]){
            gr[it]++;
        }
    }

    ///i know that the topological sort order is lst_comp...1

    for(int i = 1;i <= last_comp;i++){
        if(gr[i] == 0){
            tree[0].push_back(i);
        }
    }

    for(int i = last_comp;i;i--){
        for(auto it:ctc[i]){
            gr[it]--;
            if(gr[it] == 0){
                tree[i].push_back(it);
            }
        }
    }

    solve(0);

    fprintf(g,"%d\n",dp[0][k]);

    fclose(f);
    fclose(g);

    return 0;
}
