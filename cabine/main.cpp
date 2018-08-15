#include <cstdio>
using namespace std;
FILE *f = fopen("cabine.in","r");
FILE *g = fopen("cabine.out","w");
int V[100005];
int N,K,last = 2;
int main(){
    fscanf(f,"%d %d",&N,&K);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
    }
    if(V[1] == 0){
        V[1] = last++;
    }
    if(V[N] == 0){
        V[N] = last++;
    }
    for(int i = N - 1;i;i--){
        if(V[i] == 0 && V[i + 1] == 0){
            V[i] = last++;
        }
    }
    for(int i = 1;i <= N;i++){
        if(!V[i]){
            V[i] = last++;
        }
    }
    int ans = 0;
    for(int i = 1;i <= N;i++){
        if(V[i] - 1 == K){
            ans = i;
        }
    }
    fprintf(g,"%d",ans);
    fclose(f);
    fclose(g);
    return 0;
}
