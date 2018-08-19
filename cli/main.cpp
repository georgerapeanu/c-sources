#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f = fopen("cli.in","r");
FILE *g = fopen("cli.out","w");
int N,K;
char C[1000006];
struct Trie{
    Trie *fiu[26];
    bool isLeaf;
    int lvl;
    vector<int> dp;
    Trie(){
        memset(fiu,NULL,sizeof(fiu));
        isLeaf = 0;
        dp.clear();
    }
}*T;
void add(Trie *T,char *C){
    if(*C == '\n' || *C == '\0'){
        T -> isLeaf = 1;
        return ;
    }
    if(T -> fiu[*C - 'a'] == NULL){
        T -> fiu[*C - 'a'] = new Trie;
    }
    add(T -> fiu[*C - 'a'],C + 1);
}
void dfs(Trie *T){
    int bigChild = -1;
    for(int i = 0;i < 26;i++){
        if(T -> fiu[i] != NULL){
            T -> fiu[i] -> lvl = T -> lvl + 1;
            dfs(T -> fiu[i]);
            if(bigChild == -1 || T -> fiu[i] -> dp.size() > T -> fiu[bigChild] -> dp.size()){
                bigChild = i;
            }
        }
    }
    if(bigChild >= 0){
        swap(T -> dp,T -> fiu[bigChild] -> dp);
    }
    if(T -> dp.size() == 0){
        T -> dp.push_back(0);
    }
    for(int i = 1;i < (int)T -> dp.size();i++){
        T -> dp[i] += 1;
    }
    for(int i = 0;i < 26;i++){
        if(i != bigChild && T -> fiu[i] != NULL){
            int sz = T -> dp.size();
            for(int j = 0;T -> dp.size() <= K && j < (int)T -> fiu[i] -> dp.size();j++){
                T -> dp.push_back(1 << 28);
            }
            for(int j = sz - 1;j >= 0;j--){
                for(int k = 0;k < T -> fiu[i] -> dp.size() && j + k <= K;k++){
                    T -> dp[j + k] = min(T -> dp[j + k],T -> dp[j] + T -> fiu[i] -> dp[k] + (k > 0));
                }
            }
        }
    }
    if(T -> isLeaf){
        if(T -> dp.size() <= K)T -> dp.push_back(1 << 28);
        for(int i = (int)T -> dp.size() - 1;i;i--){
            T -> dp[i] = min(T -> dp[i],T -> dp[i - 1]);
        }
    }
}
int main(){
    T = new Trie;
    fscanf(f,"%d %d\n",&N,&K);
    for(int i = 1;i <= N;i++){
        fgets(C + 1,1000005,f);
        add(T,C + 1);
    }
    dfs(T);
    for(int i = 1;i <= K;i++){
        fprintf(g,"%d\n",T -> dp[i] * 2);
    }
    fclose(f);
    fclose(g);
    return 0;
}
