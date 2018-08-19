#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("elicop.in","r");
FILE *g = fopen("elicop.out","w");
int N,M;
bool V[105][105];
bool U[45];
int ceva = 0;
int eval(int x1,int y1,int x2,int y2,int sens){
    ceva = 0;
    int rez = 0;
    if(y1 > y2){
        swap(x1,x2);
        swap(y1,y2);
    }
    if(sens == -1){
        if(x1 < x2){
            for(int i = x1;i <= x2;i++){
                for(int j = y1;j <= y1 + i - x1;j++){
                    rez += (V[i][j] == 0);
                    ceva += (V[i][j] == 1);
                }
            }
        }
        else{
            for(int i = x1;i >= x2;i--){
                for(int j = y1 + x1 - i;j <= y2;j++){
                    rez += (V[i][j] == 0);
                    ceva += (V[i][j] == 1);
                }
            }
        }
    }
    else{
        if(x1 < x2){
            for(int i = x1;i <= x2;i++){
                for(int j = y1 + i - x1;j <= y2;j++){
                    rez += (V[i][j] == 0);
                    ceva += (V[i][j] == 1);
                }
            }
        }
        else{
            for(int i = x1;i >= x2;i--){
                for(int j = y1;j <= y1 + x1 - i;j++){
                    rez += (V[i][j] == 0);
                    ceva += (V[i][j] == 1);
                }
            }
        }
    }
    return rez;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            fscanf(f,"%d",&V[i][j]);
        }
    }
    int Q;
    fscanf(f,"%d",&Q);
    int rez = 0,nr = 0;
    for(int i = 1;i <= Q;i++){
        int x1,x2,y1,y2,sens;
        fscanf(f,"%d %d %d %d %d",&x1,&y1,&x2,&y2,&sens);
        int tmp = eval(x1,y1,x2,y2,sens);
        if(!tmp){
            rez++;
        }
        if(tmp > ceva){
            nr++;
            U[i] = 1;
        }
    }
    fprintf(g,"%d\n%d ",rez,nr);
    for(int i = 1;i <= Q;i++){
        if(U[i]){
            fprintf(g,"%d ",i);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
