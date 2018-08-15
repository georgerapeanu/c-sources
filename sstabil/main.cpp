#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("sstabil.in","r");
FILE *g = fopen("sstabil.out","w");
int N;
int V[1000005];
int dp[20][11];
int maxCf[1000005];
int main(){
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&V[i]);
        if(V[i] == 0){
            N--;
            i--;
        }
    }
    for(int i = N;i;i--){
        for(int j = 0;j < 10;j++){
            dp[i % 20][j] = -(1e6);
        }
        for(int j = i + 1,s = V[i];s < 10 && j <= N + 1;j++){
            dp[i % 20][s] = max(dp[i % 20][s],dp[j % 20][10 - s] + 1);
            s += V[j];
        }
        for(int j = 9;j >= 0;j--){
            dp[i % 20][j] = max(dp[i % 20][j],dp[i % 20][j + 1]);
        }
        maxCf[i] = dp[i % 20][0];
    }
    int cf = 0,nrcf = maxCf[1];
    for(int i = 1;i <= N;i++){
        if(cf + V[i] > 9 || maxCf[i + 1] < nrcf - 1){
            nrcf--;
            fprintf(g,"%d",cf);
            cf = 0;
        }
        cf += V[i];
    }
    fprintf(g,"%d ",cf);
    fclose(f);
    fclose(g);
    return 0;
}
