#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f = fopen("arbfind.in","r");
FILE *g = fopen("arbfind.out","w");
int N,M;
vector<int> G1[32005];
vector<int> G2[32005];
int lin1[64005],len1;
int lin2[64005],len2;
int fst[32005];
int lst[32005];
int T1[64005];
int T2[64005];
int R[64005];
int S[64005];
void dfs1(int nod){
    lin1[++len1] = 1;
    for(auto it:G1[nod]){
        dfs1(it);
    }
    lin1[++len1] = 0;
}
void dfs2(int nod){
    lin2[++len2] = 1;
    fst[nod] = len2;
    for(auto it:G2[nod]){
        dfs2(it);
    }
    lst[nod] = len2;
    lin2[++len2] = 0;
}
void dfs3(int nod){
    for(auto it:G2[nod]){
        dfs3(it);
    }
    int st = fst[nod];
    int dr = min(lst[nod],fst[nod] + T2[fst[nod]] - 1);
    R[nod] = S[dr] - S[st - 1];
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        int len;
        fscanf(f,"%d",&len);
        while(len--){
            int x;
            fscanf(f,"%d",&x);
            G1[i].push_back(x);
        }
    }
    fscanf(f,"%d",&M);
    for(int i = 1;i <= M;i++){
        int len;
        fscanf(f,"%d",&len);
        while(len--){
            int x;
            fscanf(f,"%d",&x);
            G2[i].push_back(x);
        }
    }
    dfs1(1);lin1[2 * N + 1] = 2;
    dfs2(1);lin2[2 * M + 1] = 3;
    T1[1] =  N;
    int last = 0;
    for(int i = 2;i <= 2 * N;i++){
        if(last + T1[last] - 1 >= i){
            T1[i] = min(T1[i - last + 1],last + T1[last] - i);
        }
        while(lin1[i + T1[i]] == lin1[T1[i] + 1]){
            T1[i]++;
        }
        if(i + T1[i] > last + T1[last]){
            last = i;
        }
    }
    last = 0;
    for(int i = 1;i <= 2 * M;i++){
        S[i] = lin2[i] + S[i - 1];
        if(last + T2[last] - 1 >= i){
            T2[i] = min(T1[i - last + 1],last + T2[last] - i);
        }
        while(lin2[i + T2[i]] == lin1[T2[i] + 1]){
            T2[i]++;
        }
        if(i + T2[i] > last + T2[last]){
            last = i;
        }
    }
    dfs3(1);
    for(int i = 1;i <= M;i++){
        fprintf(g,"%d\n",R[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
