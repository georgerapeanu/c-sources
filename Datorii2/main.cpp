#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("datorii2.in","r");
FILE *g = fopen("datorii2.out","w");
int N,M,C;
int dp[1 << 20];
int last[1 << 20];
int V[20];
void solve(int conf){
    if(!conf){
        return;
    }
    solve(conf ^ (1 << last[conf]));
    for(int i = 0;i < N;i++){
        if((conf ^ (1 << last[conf])) & (1 << i)){
            if(V[last[conf] + 1] * V[i + 1] >= 0){
                continue;
            }
            if(V[i + 1] < V[last[conf] + 1]){
                int a = V[i + 1];
                int b = V[last[conf] + 1];
                int c = min(-a,b);
                a = -c;
                b = c;
                V[last[conf] + 1] += a;
                V[i + 1] += b;
                fprintf(g,"%d %d %d\n",last[conf] + 1,i + 1,c);
            }
            else if(V[i + 1] > V[last[conf] + 1]){
                int a = V[i + 1];
                int b = V[last[conf] + 1];
                int c = min(a,-b);
                a = c;
                b = -c;
                V[last[conf] + 1] += a;
                V[i + 1] += b;
                fprintf(g,"%d %d %d\n",i + 1,last[conf] + 1,c);
            }
        }
    }
}
int main(){
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= M;i++){
        int x,y,z;
        fscanf(f,"%d %d %d",&x,&y,&z);
        V[x] += z;
        V[y] -= z;
    }
    for(int conf = 1;conf < (1 << N);conf++){
        dp[conf] = 1 << 28;
        int S = 0;
        for(int i = 0;i < N;i++){
            if((conf >> i) & 1){
                if(dp[conf] > dp[conf ^ (1 << i)]){
                    dp[conf] = dp[conf ^ (1 << i)];
                    last[conf] = i;
                }
                S += V[i + 1];
            }
        }
        dp[conf] += (S != 0);
    }
    int S = 0;
    for(int i = 1;i <= N;i++){
        S += abs(V[i]);
    }
    S /= 2;
    fprintf(g,"%d %d\n",dp[(1 << N) - 1],S);
    solve((1 << N) - 1);
    fclose(f);
    fclose(g);
    return 0;
}
