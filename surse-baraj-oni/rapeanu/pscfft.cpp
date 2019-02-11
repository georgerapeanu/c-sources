#include <cstdio>
using namespace std;
FILE *f = fopen("pscfft.in","r");
FILE *g = fopen("pscfft.out","w");
int T,N,S;
int V[500005];
int getnum(int pos){
    int rez = 0;
    while(pos){
        rez += pos % S;
        pos /= S;
    }
    return rez % S;
}
int main(){
    fscanf(f,"%d",&T);
    for(int k = 1;k <= T;k++){
        fscanf(f,"%d %d",&N,&S);
        for(int i = 1;i <= N;i++){
            fscanf(f,"%d",&V[i]);
        }
        bool ok2 = 1;
        for(int i = 0;i <= (3e6) / T;i++){
            bool ok = 1;
            for(int j = i;j < i + N;j++){
                if(V[j - i + 1] != getnum(j)){
                    ok = 0;
                    break;
                }
            }
            if(ok){
                fprintf(g,"%d\n",i);
                ok2 = 0;
                break;
            }
        }
        if(ok2){
            fprintf(g,"-1\n");
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
