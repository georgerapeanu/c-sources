#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int N,M,H;
int h[int(1e5) + 5];
int X[int(1e5) + 5];
int Y[int(1e5) + 5];
vector<int> G[int(1e5) + 5];
vector<vector<int> > ctc;
bool inst[100005];
int st[100005];
int len;
int id[100005];
int low[100005];
int lastid;
int T[100005];
int gr[100005];
int fi(int nod){
    if(T[nod] < 0){
        return nod;
    }
    return T[nod] = fi(T[nod]);
}
void u(int x,int y){
    x = fi(x);
    y = fi(y);
    if(T[x] < T[y]){
        T[x] += T[y];
        T[y] = x;
    }
    else{
        T[y] += T[x];
        T[x] = y;
    }
}
void dfs(int nod){
   st[++len] = nod;
   inst[nod] = 1;
   id[nod] = low[nod] = ++lastid;
   for(auto it:G[nod]){
      if(!id[it]){
         dfs(it);
      }
      if(inst[it]){
         low[nod] = min(low[nod],low[it]);
      }
   }
   if(low[nod] == id[nod]){
      vector<int> tmp;
      while(st[len] != nod){
         tmp.push_back(st[len]);
         inst[st[len]] = 0;
         len--;
      }
      tmp.push_back(st[len]);
      inst[st[len]] = 0;
      len--;
      for(int i = 1;i < (int)tmp.size();i++){
        u(tmp[i - 1],tmp[i]);
      }
      ctc.push_back(tmp);
   }
}
int main()
{
    scanf("%d %d %d",&N,&M,&H);
    for(int i = 1;i <= N;i++){
        scanf("%d",&h[i]);
        T[i] = -1;
    }
    for(int i = 1;i <= M;i++){
        scanf("%d %d",&X[i],&Y[i]);
        if((h[X[i]] + 1) % H == h[Y[i]]){
            G[X[i]].push_back(Y[i]);
        }
        if((h[Y[i]] + 1) % H == h[X[i]]){
            G[Y[i]].push_back(X[i]);
        }
    }
    for(int i = 1;i <= N;i++){
        if(!id[i]){
            dfs(i);
        }
    }
    for(int i = 1;i <= M;i++){
        if((h[X[i]] + 1) % H == h[Y[i]]){
            int x = fi(X[i]);
            int y = fi(Y[i]);
            if(x != y){
                gr[x]++;
            }
        }
        if((h[Y[i]] + 1) % H == h[X[i]]){
            int x = fi(X[i]);
            int y = fi(Y[i]);
            if(x != y){
                gr[y]++;
            }
        }
    }
    int best = 0;
    for(int i = 0;i < (int)ctc.size();i++){
        int wh = fi(ctc[i].back());
        if(!gr[wh] && ctc[best].size() > ctc[i].size()){
            best = i;
        }
    }
    printf("%d\n",ctc[best].size());
    for(auto it:ctc[best]){
        printf("%d ",it);
    }
    return 0;
}
