#include <cstdio>
#include <vector>
using namespace std;
FILE *f = fopen("fft2d.in","r");
FILE *g = fopen("fft2d.out","w");
int dp[2][1 << 16];
int F,T;
vector<int> V[16];
int main(){
    fscanf(f,"%d %d",&F,&T);
    for(int i = 1;i <= T;i++){
        int h,x;
        fscanf(f,"%d %d",&h,&x);
        V[h].push_back(x);
    }
    long long rez = 0;
    for(int i = 0;i < (1 << (F - 1));i++){
        dp[0][i] = 1;
    }
    for(auto it:V[0]){
        dp[0][it] = 0;
    }
    for(int h = 1;h < F;h++){
        for(int i = 0;i < (1 << (F - 1));i++){
            dp[h & 1][i] = dp[1 - (h & 1)][i] + dp[1 - (h & 1)][i ^ (1 << (F - h - 1))];
        }
        for(auto it:V[h]){
            dp[h & 1][it] = 0;
        }
    }
    for(int i = 0; i < (1 << (F - 1));i++){
        rez += dp[(F - 1) & 1][i];
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
