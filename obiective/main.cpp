#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
FILE *f = fopen("obiective.in","r");
FILE *g = fopen("obiective.out","w");
const int NMAX = 32000;
int N,M,QQ;
int lowest[20][NMAX + 5];
int tt[20][NMAX + 5];
int gr[NMAX + 5];
vector<int> G[NMAX + 5];
vector<int> DAG[NMAX + 5];
vector<int> T[NMAX + 5];
vector<int> Inapoi[NMAX + 5];
int low[NMAX + 5];
int id[NMAX + 5];
int st[NMAX + 5];
bool inst[NMAX + 5];
int len,lastid;
int comp[NMAX + 5];
int nrcomp;
int X[4 * NMAX + 5];
int Y[4 * NMAX + 5];
int root;
queue<int> Q;
int lvl[NMAX + 5];
void ctc(int nod){
   low[nod] = id[nod] = ++lastid;
   st[++len] = nod;
   inst[nod] = 1;
   for(auto it:G[nod]){
      if(!id[it]){
         ctc(it);
      }
      if(inst[it]){
         low[nod] = min(low[nod],low[it]);
      }
   }
   if(low[nod] == id[nod]){
      ++nrcomp;
      while(st[len] != nod){
         comp[st[len]] = nrcomp;
         inst[st[len]] = 0;
         len--;
      }
      len--;
      comp[nod] = nrcomp;
      inst[nod] = 0;
   }
}
void dfs2(int nod){
   lvl[N + 1] = 1 << 30;
   lowest[0][nod] = N + 1;
   for(auto it:T[nod]){
      lvl[it] = 1 + lvl[nod];
      dfs2(it);
      if(lvl[lowest[0][it]] < lvl[lowest[0][nod]]){
         lowest[0][nod] = lowest[0][it];
      }
   }
   for(auto it:Inapoi[nod]){
      if(lvl[it] < lvl[lowest[0][nod]]){
         lowest[0][nod] = it;
      }
   }
   if(lvl[tt[0][nod]] < lvl[lowest[0][nod]]){
      lowest[0][nod] = tt[0][nod];
   }
}
void prelca(){
   for(int i = 1;i <= 19;i++){
      for(int j = 1;j <= N;j++){
         tt[i][j] = tt[i - 1][tt[i - 1][j]];
         lowest[i][j] = lowest[i - 1][lowest[i - 1][j]];
      }
   }
}
int lca(int u,int v){
   if(lvl[u] > lvl[v]){
      swap(u,v);
   }
   for(int i = 19;i >= 0;i--){
      if(lvl[v] - lvl[u] >= (1 << i)){
         v = tt[i][v];
      }
   }
   if(u == v){
      return u;
   }
   for(int i = 19;i >= 0;i--){
      if(tt[i][u] != tt[i][v]){
         v = tt[i][v];
         u = tt[i][u];
      }
   }
   return tt[0][v];
}
int getlow(int nod,int cost){
   for(int i = 19;i >= 0;i--){
      if((cost >> i) & 1){
         nod = lowest[i][nod];
      }
   }
   return nod;
}
int solve(int u,int v){
   if(lvl[v] <= lvl[u]){
      return 0;
   }
   int rez = 0;
   for(int lg = 19;lg >= 0;lg--){
      if(lvl[lowest[lg][v]] > lvl[u]){
         v = lowest[lg][v];
         rez |= 1 << lg;
      }
   }
   return rez + 1;
}
int main() {
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= M;i++){
       fscanf(f,"%d %d",&X[i],&Y[i]);
       G[X[i]].push_back(Y[i]);
    }
    for(int i = 1;i <= N;i++){
       if(id[i]){
            continue;
       }
       ctc(i);
    }
    for(int i = 1;i <= M;i++){
       if(comp[X[i]] != comp[Y[i]]){
          DAG[comp[X[i]]].push_back(comp[Y[i]]);
          gr[comp[Y[i]]]++;
       }
    }
    N = nrcomp;
    for(int i = 1;i <= N;i++){
       if(!gr[i]){
          Q.push(i);
          root = i;
       }
    }
    while(!Q.empty()){
       int nod = Q.front();
       Q.pop();
       for(auto it:DAG[nod]){
          gr[it]--;
          if(!gr[it]){
             T[nod].push_back(it);
             tt[0][it] = nod;
             Q.push(it);
          }
       }
    }
    for(int i = 1;i <= M;i++){
       if(comp[X[i]] != comp[Y[i]]){
          if(tt[0][comp[Y[i]]] != comp[X[i]]){
             Inapoi[comp[Y[i]]].push_back(comp[X[i]]);
          }
       }
    }
    lvl[root] = 1;
    dfs2(root);
    prelca();
    fscanf(f,"%d",&QQ);
    while(QQ--){
       int u,v;
       fscanf(f,"%d %d",&u,&v);
       u = comp[u];
       v = comp[v];
       int w = lca(u,v);
       int rez = solve(w,u);
       fprintf(g,"%d\n",rez);
    }
    return 0;
}
