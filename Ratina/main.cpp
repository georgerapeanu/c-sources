#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f = fopen("ratina.in","r");
FILE *g = fopen("ratina.out","w");
const int NMAX = 10000;
const int LMAX = 2000;
const int TOTALLMAX = 200000;
int last;
struct Trie{
    int id;
    Trie *fiu[26];
    Trie(){
        memset(fiu,0,sizeof(fiu));
        id = ++last;
    }
}*T;
int N,M;
char C[NMAX + 5][LMAX + 5];
int ord[NMAX + 5];
int lvl[TOTALLMAX + 5];
int RMQ[17][2 * TOTALLMAX + 5];
vector<int> term[TOTALLMAX + 5];
int euler[2 * TOTALLMAX + 5],sz;
int lg2[2 * TOTALLMAX + 5];
int nod[NMAX + 5];
int frst[2 * TOTALLMAX + 5];
int lrst[2 * TOTALLMAX + 5];
void ins(Trie *T,char *C,int &i){
    if(*C == '\n' || *C == '\0'){
        term[T -> id].push_back(i);
        return;
    }
    if(T -> fiu[*C - 'a'] == NULL){
        T -> fiu[*C - 'a'] = new Trie;
    }
    ins(T -> fiu[*C - 'a'],C + 1,i);
}
void dfs(Trie *T){
    for(auto it:term[T -> id]){
        ord[it] = ++last;
        nod[it] = T -> id;
    }
    euler[++sz] = T -> id;
    RMQ[0][sz] = T -> id;
    frst[T -> id] = sz;
    for(int i = 0;i < 26;i++){
        if(T -> fiu[i] != NULL){
            lvl[T -> fiu[i] -> id] = lvl[T -> id] + 1;
            dfs(T -> fiu[i]);
            euler[++sz] = T -> id;
            RMQ[0][sz] = T -> id;
        }
    }
    lrst[T -> id] = sz;
}
int preRMQ(){
    for(int i = 2;i <= sz;i++){
        lg2[i] = 1 + lg2[i >> 1];
    }
    for(int j = 1;j < 17;j++){
        for(int i = 1;i <= sz;i++){
            RMQ[j][i] = RMQ[j - 1][i];
            if(i >= (1 << (j - 1)) && lvl[RMQ[j - 1][i - (1 << (j - 1) )]] < lvl[RMQ[j][i]]){
                RMQ[j][i] = RMQ[j - 1][i - (1 << (j - 1) )];
            }
        }
    }
}
int lca(int a,int b){
    if(b < a){
        swap(a,b);
    }
    int tmp1 = RMQ[lg2[b - a + 1]][b];
    int tmp2 = RMQ[lg2[b - a + 1]][a + (1 << lg2[b - a + 1]) - 1];
    return min(lvl[tmp1],lvl[tmp2]) - 1;
}
int main(){
    T = new Trie;
    fscanf(f,"%d %d\n",&N,&M);
    for(int i = 1;i <= N;i++){
        fgets(C[i] + 1,2005,f);
        ins(T,C[i] + 1,i);
    }
    last = 0;
    lvl[T -> id] = 1;
    dfs(T);
    preRMQ();
    while(M--){
        int t;
        fscanf(f,"%d",&t);
        int fst = 0,lst = 0;
        while(t--){
            int x;
            fscanf(f,"%d",&x);
            if(fst == 0 || ord[x] < ord[fst]){
                fst = x;
            }
            if(lst == 0 || ord[x] > ord[lst]){
                lst = x;
            }
        }
        fprintf(g,"%d\n",lca(frst[nod[fst]],frst[nod[lst]]));
    }
    fclose(f);
    fclose(g);
    return 0;
}
