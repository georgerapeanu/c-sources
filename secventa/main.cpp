#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("secventa.in","r");
FILE *g = fopen("secventa.out","w");

int N,K;
int V[500005];
int D[500005],stq,drq;
int ma = -3000000,Ind;

const int LEN = 1e4;
char buff[LEN];
int ind = LEN - 1;
int i32(){
    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    int rez = 0,sgn = 1;
    if(buff[ind] == '-'){
        sgn *= -1;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9'){
        rez = rez * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return rez * sgn;
}

int main(){
    N = i32();
    K = i32();
    for(int i = 1;i <= N;i++){
        V[i] = i32();
    }

    stq = 1;drq = 0;
    for(int i = 1;i <= N;i++){
        while(stq <= drq && D[stq] <= i - K){
            stq++;
        }
        while(stq <= drq && V[D[drq]] > V[i]){
            drq--;
        }
        D[++drq] = i;
        if(i >= K && V[D[stq]] > ma){
            ma = V[D[stq]];
            Ind = i - K + 1;
        }
    }

    fprintf(g,"%d %d %d",Ind,Ind + K - 1,ma);
    fclose(f);
    fclose(g);

    return 0;
}
