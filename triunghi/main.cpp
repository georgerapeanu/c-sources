#include <cstdio>
#include <cstring>

using namespace std;

FILE *f = fopen("triunghi.in","r");
FILE *g = fopen("triunghi.out","w");

int N,S;
int coef[20];
int tmp_coef[20][20];
bool rucsac[20][1000005];
bool ant[20][1000005];
int V[20][20];

int main(){

    fscanf(f,"%d %d",&N,&S);

    for(int i = 1;i <= N;i++){
        tmp_coef[N][i] = coef[i] = 1;
        tmp_coef[N][i - 1] = 0;
        for(int j = N - 1;j;j--){
            for(int k = 1;k <= j;k++){
                tmp_coef[j][k] = tmp_coef[j + 1][k] + tmp_coef[j + 1][k + 1];
                coef[i] += tmp_coef[j][k];
            }
            tmp_coef[j][j + 1] = 0;
        }
    }

    rucsac[0][0] = 1;
    for(int i = 1;i <= N;i++){
        for(int j = 0;j <= S;j++){
            if(j < coef[i]){
                continue;
            }
            if(rucsac[i - 1][j - coef[i]]){
                rucsac[i][j] = 1;
            }
            else if(rucsac[i][j - coef[i]]){
                rucsac[i][j]  = 1;
                ant[i][j] = 1;
            }
        }
    }

    if(!rucsac[N][S]){
        fputs("imposibil\n",g);
        return 0;
    }

    int x = N,y = S;
    while(x && y){
        V[N][x]++;
        y -= coef[x];
        if(!ant[x][y + coef[x]]){
            x--;
        }
    }

    for(int i = N - 1;i;i--){
        for(int j = 1;j <= i;j++){
            V[i][j] = V[i + 1][j] + V[i + 1][j + 1];
        }
    }

    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= i;j++){
            fprintf(g,"%d ",V[i][j]);
        }
        fputc('\n',g);
    }

    fclose(f);
    fclose(g);

    return 0;
}
