#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f = fopen("piramid.in","r");
FILE *g = fopen("piramid.out","w");
int N;
char C[1005][1005];
char NC[1005][1005];
int LD[1005][1005];
int RD[1005][1005];
int L[1005][1005];
int AIB[1005],rez;
int ord[1005];
vector<int> elim[1005];
void u(int pos,int val){
    for(;pos <= 1000;pos += (-pos) & pos){
        AIB[pos] += val;
    }
}
int q(int pos){
    int rez = 0;
    for(;pos;pos -= (-pos) & pos){
        rez += AIB[pos];
    }
    return rez;
}
void proc(int x,int y){
    for(;x && y;x--,y--){
        for(auto it:elim[x]){
            u(it,-1);
        }
        elim[x].clear();
        if(C[x][y] == '0'){
            continue;
        }
        int len = min(RD[x][y],LD[x][y]) - 1;
        rez += q(x + len);
        if(L[x][y] + x <= x + y){
            u(x,1);
            int dif = y - L[x][y];
            int x_rip = x - (dif / 2) - 1;
            if(x_rip <= 0){
                elim[0].push_back(x);
            }
            else if(x_rip == x){
                u(x,-1);
            }
            else{
                elim[x_rip].push_back(x);
            }
        }
    }
    while(x >= 0){
        for(auto it:elim[x]){
            u(it,-1);
        }
        elim[x].clear();
        x--;
    }
}
int main(){
    fscanf(f,"%d\n",&N);
    for(int i = 1;i <= N;i++){
        fgets(C[i] + 1,1005,f);
    }
    for(int k = 0;k < 4;k++){
        for(int i = N;i;i--){
            for(int j = 1;j <= N;j++){
                if(C[i][j] == '1'){
                    LD[i][j] = 1 + LD[i + 1][j - 1];
                    RD[i][j] = 1 + RD[i + 1][j + 1];
                    L[i][j] = (L[i][j - 1] ? L[i][j - 1] : j);
                }
                else{
                    L[i][j] = LD[i][j] = RD[i][j] = 0;
                }
            }
        }
        for(int k = 1;k <= N;k++){
            proc(k,N);
        }
        for(int k = N - 1;k;k--){
            proc(N,k);
        }
        for(int i = 1;i <= N;i++){
            for(int j = 1;j <= N;j++){
                NC[j][N - i + 1] = C[i][j];
            }
        }
        memcpy(C,NC,sizeof(NC));
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
