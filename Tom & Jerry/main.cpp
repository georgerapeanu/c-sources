#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;
FILE *f = fopen("tj.in","r");
FILE *g = fopen("tj.out","w");
bitset<260> G[260];
int T;
int N,M;
bool U[260];
int main(){
    fscanf(f,"%d",&T);
    while(T--){
        memset(U,0,sizeof(U));
        fscanf(f,"%d %d",&N,&M);
        for(int i = 1;i <= N;i++){
            G[i].reset();
            G[i][i] = 1;
        }
        while(M--){
            int x,y;
            fscanf(f,"%d %d",&x,&y);
            G[x][y] = 1;
            G[y][x] = 1;
        }
        bool ok = 1;
        for(int t = 1;t < N;t++){
            int found  = 0;
            for(int i = 1;i <= N;i++){
                if(U[i]){
                    continue;
                }
                for(int j = 1;j <= N;j++){
                    if(U[j] || i == j){
                        continue;
                    }
                    if((G[i] & G[j]) == G[j]){
                        found = j;
                        goto done;
                    }
                }
            }
            done:;
            if(found){
                U[found] = 1;
                for(int i = 1;i <= N;i++){
                    G[i][found] = 0;
                }
            }
            else{
                ok = 0;
                goto done2;
            }
        }
        done2:;
        if(ok){
            fprintf(g,"DA\n");
        }
        else{
            fprintf(g,"NU\n");
        }
    }
    return 0;
}
