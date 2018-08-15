#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
FILE *f = fopen("restrict.in","r");
FILE *g = fopen("restrict.out","w");
int N,K;
int P[100005];
int C[100005];
int R[100005];
int T[100005];
vector<int> G[100005];
vector<int> V;
void dfs(int nod,int tata){
    V.push_back(nod);
    if(R[nod] != -1){
        set<int> S;
        bool ok = 0;
        for(int i = (int)V.size() - 1;i >= 0;i--){
            if(S.find(V[i]) != S.end()){
                ok = (V[i] != R[nod]);
            }
            if(R[V[i]] != -1){
                S.insert(R[V[i]]);
            }
        }
        if(ok){
            T[nod] = C[nod] + T[tata];
        }
        int pos = 0;
        while(V[pos] != R[nod]){
            pos++;
        }
        long long SS = 0;
        for(int i = pos + 1;i < (int)V.size();i++){
            SS += C[V[i]];
        }
        long long tmp = 1LL << 60;
        for(int i = pos + 2;i < (int)V.size() - 1;i++){
            tmp = min(((K - ((int)V.size() - pos - 1) + 1) / 2) * 2LL * C[V[i]],tmp);
        }
        if(tmp >= (1LL << 60)){
            T[nod] = -1;
        }
        else{
            T[nod] = T[R[nod]] + SS + tmp;
        }
    }
    else{
        T[nod] = C[nod] + T[tata];
    }
    if(T[nod] >= 0){
        for(auto it:G[nod]){
            dfs(it,nod);
        }
    }
    V.pop_back();
}
int main(){
    K++;
    fscanf(f,"%d %d",&N,&K);
    for(int i = 2;i <= N;i++){
        fscanf(f,"%d %d %d",&P[i],&C[i],&R[i]);
        G[P[i]].push_back(i);
    }
    R[1] = -1;
    dfs(1,0);
    for(int i = 1;i <= N;i++){
        fprintf(g,"%d\n",T[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
