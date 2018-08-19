#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
FILE *f = fopen("interesant.in","r");
FILE *g = fopen("interesant.out","w");
char C[205][5005];
int len[205];
int N,P,rez;
bool U[205];
bool in(int i,int j){
    int ind = 1;
    for(int k = 1;k <= len[j];k++){
        ind += (C[i][ind] == C[j][k]);
        if(ind > len[i]){
            return 1;
        }
    }
    return 0;
}
int main()
{
    fscanf(f,"%d %d\n",&P,&N);
    rez = N;
    for(int i = 1;i <= N;i++){
        fgets(C[i] + 1,5005,f);
        len[i] = strlen(C[i] + 1);
        if(C[i][len[i]] == '\n'){
            C[i][len[i]] = '\0';
            len[i]--;
        }
    }
    if(P == 1){
        int rez = 1;
        for(int i = 2;i <= N;i++){
            if(len[i] > len[rez] || (len[i] == len[rez] && strcmp(C[i] + 1,C[rez] + 1) < 0)){
                rez = i;
            }
        }
        fputs(C[rez] + 1,g);
    }
    else{
        for(int i = 1;i <= N;i++){
            for(int j = 1;j <= N;j++){
                if(i != j && len[j] > len[i] && in(i,j)){
                    U[i] = 1;
                    rez--;
                    break;
                }
            }
        }
        fprintf(g,"%d\n",rez);
        for(int i = 1;i <= N;i++){
            if(U[i]){
                continue;
            }
            fputs(C[i] + 1,g);
            fputc('\n',g);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
