#include <cstdio>
#include <algorithm>
#include <queue>
 
using namespace std;
 
FILE *f = fopen("cangrena.in","r");
FILE *g = fopen("cangrena.out","w");
 
int N,M;
long long mini[100005];
long long maxi[100005];
int V[100005];
vector<int> G[100005];
queue<int> Q;
bool inQ[100005];
 
void bellmand(long long *Out,int sgn,int cst){
    for(int i = 1;i <= N;i++){
        Out[i] = sgn * (1LL << 60);
        if(V[i] != -1){
            Out[i] = V[i];
            Q.push(i);
            inQ[i] = 1;
        }
    }
     
    while(!Q.empty()){
        int nod = Q.front();
        Q.pop();
		inQ[nod] = 0;
        for(auto it:G[nod]){
            if(Out[it] * sgn > (Out[nod] + cst * sgn) * sgn){
                Out[it] = (Out[nod] + cst * sgn);
                if(!inQ[it]){
                    Q.push(it);
					inQ[it] = 1;
                }
            }
        }
    }
}
 
bool check(int diff){
    bellmand(maxi,1,diff);
    bellmand(mini,-1,diff);
    for(int i = 1;i <= N;i++){
        if(maxi[i] < mini[i]){
            return 0;
        }
    }
    return 1;
}
 
int main(){
     
    fscanf(f,"%d %d",&N,&M);
     
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
    }
     
    for(int i = 1;i <= M;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
     
    int st = -1,dr = 1e9;
    while(dr - st > 1){
        int mid = (st + dr) / 2;
        if(check(mid)){
            dr = mid;
        }
        else{
            st = mid;
        }
    }
     
    check(dr);
     
    for(int i = 1;i <= N;i++){
        fprintf(g,"%lld ",maxi[i]);
    }
     
    fclose(f);
    fclose(g);
     
    return 0;
}