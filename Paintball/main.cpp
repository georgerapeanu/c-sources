#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f = fopen("paintball.in","r");
FILE *g = fopen("paintball.out","w");
int N;
int V[1000005];
vector<int> cycle;
vector<int> G[1000005];
int st[1000005];
int len,maxi,mini;
int viz[1000005];
int viz2[1000005];
bool mort[1000005];
bool on_cycle[1000005];
void dfs(int nod){
    st[++len] = nod;
    viz[nod] = len;
    if(!viz[V[nod]]){
        dfs(V[nod]);
    }
    else{
        for(int i = viz[V[nod]];i <= len;i++){
            cycle.push_back(st[i]);
            on_cycle[st[i]] = 1;
        }
    }
    len--;
}
int dfs2(int nod){
    viz[nod] = 1;
    if(on_cycle[nod]){
        return 0;
    }
    int rez = 0;
    for(auto it:G[nod]){
        rez += dfs2(it);
    }
    rez += (!G[nod].empty());
    return rez;
}
int main(){
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
        G[V[i]].push_back(i);
    }
    for(int i = 1;i <= N;i++){
        if(!viz[i]){
            cycle.clear();
            dfs(i);
            if(cycle.size() == 1){
                mini++;
                maxi++;
                continue;
            }
            bool start = 0;
            for(auto it:cycle){
                viz[it] = 1;
                if(G[it].size() > 1){
                    start = 1;
                }
                for(auto it2:G[it]){
                    maxi += dfs2(it2);
                }
            }
            maxi += (int)cycle.size() - (!start);
        }
    }
    fprintf(g,"%d %d",mini,maxi);
    fclose(f);
    fclose(g);
    return 0;
}
