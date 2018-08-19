#include <cstdio>
using namespace std;
FILE *f = fopen("oras.in","r");
FILE *g = fopen("oras.out","w");
int N;
char G[205][205];
int st;
int main()
{
    fscanf(f,"%d",&N);
    if(N == 1){
        fprintf(g,"1");
        return 0;
    }
    if(N == 2 || N == 4){
        fprintf(g,"-1");
        return 0;
    }
    if(N & 1){
        G[1][2] = '1';
        G[2][3] = '1';
        G[3][1] = '1';
        st = 5;
    }
    else{
        G[1][2] = '1';
        G[2][3] = '1';
        G[3][1] = '1';
        G[4][5] = '1';
        G[5][6] = '1';
        G[6][4] = '1';
        G[1][4] = '1';
        G[4][3] = '1';
        G[2][6] = '1';
        G[6][1] = '1';
        G[3][5] = '1';
        G[5][2] = '1';
        G[2][4] = '1';
        G[1][5] = '1';
        G[3][6] = '1';
        st = 8;
    }
    for(;st <= N;st += 2){
        G[st - 1][st] = '1';
        for(int i = 1;i <= st - 2;i++){
            G[i][st - 1] = '1';
            G[st][i] = '1';
        }
    }
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            if(!G[i][j]){
                G[i][j] = '0';
            }
        }
        fputs(G[i] + 1,g);
        fputc('\n',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
