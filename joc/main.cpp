#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("joc.in","r");
FILE *g = fopen("joc.out","w");

int N,M;
int V[1005][1005];
int A[1005][1005];
int B[1005][1005];
int MAXA[1005][1005];
int MINB[1005][1005];

int main(){
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            fscanf(f,"%d",&V[i][j]);
        }
    }

    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            if(i == 1 && j == 1){
                A[i][j] = MAXA[i][j] = V[i][j];
                B[i][j] = MINB[i][j] = -V[i][j];
                continue;
            }
            A[i][j] = min((j != 1 ? MINB[i][j - 1] :  (1 << 30)),(i != 1 ? MINB[i - 1][j] : (1 << 30))) + V[i][j];
            B[i][j] = max((j != 1 ? MAXA[i][j - 1] : -(1 << 30)),(i != 1 ? MAXA[i - 1][j] : -(1 << 30))) - V[i][j];
            MINB[i][j] = min(B[i][j],min((i == 1 ? (1 << 30) : MINB[i - 1][j]),(j == 1 ? (1 << 30):MINB[i][j - 1])));
            MAXA[i][j] = max(A[i][j],max((i == 1 ? -(1 << 30) : MAXA[i - 1][j]),(j == 1 ? -(1 << 30):MAXA[i][j - 1])));
        }
    }

    int x = 1,y = 1;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            if(A[x][y] < A[i][j]){
                x = i;
                y = j;
            }
        }
    }

    fprintf(g,"%d %d %d",A[x][y],x,y);

    fclose(f);
    fclose(g);

    return 0;
}
