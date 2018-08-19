#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f = fopen("salsa.in","r");
FILE *g = fopen("salsa.out","w");
int N;
int nxt[100005];
vector<int> G[100005];
vector<int> cycle;
int viz[100005];
int st[100005],len;
int inst[100005];
int maxMove[100005];
int fr[100005];
void dfs(int nod){
    st[++len] = nod;
    inst[nod] = len;
    viz[nod]++;
    if(inst[nxt[nod]]){
        for(int i = inst[nxt[nod]];i <= len;i++){
            cycle.push_back(st[i]);
        }
        return ;
    }
    dfs(nxt[nod]);
    len--;
    inst[nod] = 0;
}
void dfs2(int nod){
    for(auto it:G[nod]){
        if(viz[it] < 2){
            viz[it] = 2;
            maxMove[it] = maxMove[nod] + 1;
            dfs2(it);
        }
    }
}
int main(){
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&nxt[i]);
        G[nxt[i]].push_back(i);
    }
    for(int i = 1;i <= N;i++){
        if(!viz[i]){
            len = 0;
            cycle.clear();
            dfs(i);
            for(auto it:cycle){
                maxMove[it] = cycle.size();
                viz[it]++;
            }
            for(auto it:cycle){
                dfs2(it);
            }
        }
    }
    for(int i = 1;i <= N;i++){
        fr[maxMove[i]]++;
    }
    for(int i = N;i >= 0;i--){
        fr[i] += fr[i + 1];
    }
    for(int i = 1;i <= N;i++){
        fprintf(g,"%d\n",fr[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
