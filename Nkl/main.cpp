#include <cstdio>
#include <vector>
using namespace std;
FILE *f = fopen("nkl.in","r");
FILE *g = fopen("nkl.out","w");
int N,K,L,Q;
vector<int> E;
const int MOD = (1e9) + 7;
int adun(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}
int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}
int mult(int a,int b){
    return 1LL * a * b % MOD;
}
int C[1005][1005];
int P[1005][1005];
int main(){
    for(int i = 0;i <= 1000;i++){
        C[i][0] = C[i][i] = 1;
        for(int j = 1;j < i;j++){
            C[i][j] = adun(C[i - 1][j],C[i - 1][j - 1]);
        }
    }
    for(int i = 0;i <= 1000;i++){
        P[i][0] = 1;
        for(int j = 1;j <= 1000;j++){
            P[i][j] = mult(P[i][j - 1],i);
        }
    }
    fscanf(f,"%d",&N);
    for(int i = 2;1LL * i * i <= N;i++){
        if(N % i == 0){
            E.push_back(0);
            while(N % i == 0){
                E[(int)E.size() - 1]++;
                N /= i;
            }
        }
    }
    if(N != 1){
        E.push_back(1);
    }
    fscanf(f,"%d",&Q);
    while(Q--){
        fscanf(f,"%d %d",&K,&L);
        int rez = 1;
        for(auto it:E){
            int tmp = 0;
            for(int num = L - 1;num >= 0;num--){
                tmp = adun(tmp,mult(C[K][num],P[it][num]));
            }
            rez = mult(rez,tmp);
        }
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
