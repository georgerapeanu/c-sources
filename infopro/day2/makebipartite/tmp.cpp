#include <algorithm>
	
#include <cstdio>
	
#include <vector>
	
 
	
using namespace std;
	
 
	
const int DEB = 0;
	
const int NMAX = 1e6;
	
 
	
FILE *f = fopen("makebipartite.in","r");
	
FILE *g = fopen("makebipartite.out","w");
	
 
	
int n,m;
	
vector<int> graph[NMAX + 5];
	
bool viz[NMAX + 5];
	
int has_ok[NMAX + 5];
	
int has_bad[NMAX + 5];
	
int total_bad;
	
int lvl[NMAX + 5];
	
int cnt[NMAX + 5];
	
int mars[NMAX + 5];
	
int father[NMAX + 5];
	
 
	
void dfs(int nod,int tata){
	
    father[nod] = tata;
	
    viz[nod] = true;
	
    lvl[nod] = 1 + lvl[tata];
	
    for(auto it:graph[nod]){
	
        if(it == tata){
	
            continue;
	
        }
	
        if(viz[it] == false){
	
            dfs(it,nod);
	
            mars[nod] += mars[it];
	
        }
	
        else if(lvl[it] < lvl[nod] && ((lvl[nod] - lvl[it] + 1) % 2 == 1)){
	
            mars[nod]++;
	
            mars[father[it]]--;
	
            total_bad++;
	
        }
	
    }
	
    cnt[nod] = mars[nod];
	
}
	
 
	
void solve(int N,int M,int *X,int *Y,char *S){
	
 
	
    n = N;
	
    m = M;
    
    total_bad = 0;	
 
	
    for(int i = 1;i <= n;i++){
	
        graph[i].clear();
	
        viz[i] = false;
	
        lvl[i] = 0;
	
        cnt[i] = 0;
	
        mars[i] = 0;
	
	father[i] = 0;
    }
	
 
	
    for(int i = 0;i < m;i++){
	
        graph[X[i]].push_back(Y[i]);
	
        graph[Y[i]].push_back(X[i]);
	
    }
	
 
	
    for(int i = 1;i <= n;i++){
	
        if(viz[i] == false){
	
            dfs(i,0);
	
        }
	
    }
	
 
	
    for(int i = 1;i <= n;i++){
	
        S[i - 1] = (cnt[i] == total_bad) + '0';
	
    }
	
 
	
}
	
 
	
const int LEN = 1 << 12;
	
char buff[LEN];
	
int ind = LEN - 1;
	
 
	
int i32(){
	
    int ans = 0;
	
 
	
    while(buff[ind] < '0' || buff[ind] > '9'){
	
        if(++ind >= LEN){
	
            ind = 0;
	
            fread(buff,1,LEN,f);
	
        }
	
    }
	
    
	
    while(!(buff[ind] < '0' || buff[ind] > '9')){
	
        ans = ans * 10 + buff[ind] - '0';
	
        if(++ind >= LEN){
	
            ind = 0;
	
            fread(buff,1,LEN,f);
	
        }
	
    }
	
    
	
    return ans;
	
}
	
 
	
int main() {
	
 
	
    int T;
	
    T = i32();
	
    for(int t = 0; t < T; t++) {
	
        int N, M;
	
        N = i32();M = i32();
	
        int* X = (int*)malloc(sizeof(int) * M);
	
        int* Y = (int*)malloc(sizeof(int) * M);
	
        char* S = (char*)malloc(sizeof(char) * (N + 1));
	
        S[N] = '\0';
	
        for(int i = 0; i < M; i++) {
	
            int x, y;
	
            x = i32();y = i32();
	
            X[i] = x; Y[i] = y;
	
        }
	
        solve(N, M, X, Y, S);
	
        free(X); free(Y);
	
        fprintf(g,"%s\n", S);
	
        free(S);
	
    }
	
 
	
    fclose(f);
	
    fclose(g);
	
 
	
    return 0;
	
}
