#include <cstdio>
#include <vector>
using namespace std;
FILE *f = fopen("tric.in","r");
FILE *g = fopen("tric.out","w");
int N,M;
int gr[100005];
vector<int> G[100005];
vector<int> lvl[100005];
long long rez;
bool viz[100005];
int fi(vector<int> &V,int a){
    for(int i = 0;i < (int)V.size();i++){
        if(V[i] == a){
            return i;
        }
    }
    return -1;
}
int main(){
    fscanf(f,"%d %d",&N,&M);
    while(M--){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        x++;
        y++;
        G[x].push_back(y);
        G[y].push_back(x);
        gr[x]++;
        gr[y]++;
    }
    for(int i = 1;i <= N;i++){
        lvl[gr[i]].push_back(i);
    }
    int sz = N,wh = 1;
    while(sz){
        wh--;
        while(wh < 0 || lvl[wh].empty()){
            wh++;
        }
        int a = lvl[wh].back();
        lvl[wh].pop_back();
        if(viz[a]){
            continue;
        }
        viz[a] = 1;
        for(int i = 0;i < G[a].size();i++){
            if(viz[G[a][i]]){
                continue;
            }
            for(int j = i + 1;j < G[a].size();j++){
                if(!viz[G[a][j]] && fi(G[G[a][i]],G[a][j]) != -1){
                    rez++;
                }
            }
        }
        for(auto it:G[a]){
            gr[it]--;
            lvl[gr[it]].push_back(it);
        }
        sz--;
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
