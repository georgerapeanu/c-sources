#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f = fopen("echipe.in","r");
FILE *g = fopen("echipe.out","w");
pair<int,int> V[255];
pair<int,int> Sub[255];
pair<int,int> new_Sub[255];
int N,K,len;
int dp[255][255];
int pref_max[255][255];
int sol[255];
pair<int,int> D[255];
int stq,drq;
bool cmp(pair<int,int> a,pair<int,int> b){
    return a.second - a.first < b.second - b.first;
}
bool change = 1;
void baga(pair<int,int> a){
    change = 0;
    int new_len = 0;
    for(int i = 1;i <= len;i++){
        if(Sub[i].first <= a.first && a.second <= Sub[i].second){
            ;
        }
        else{
            change = 1;
            new_Sub[++new_len] = Sub[i];
        }
    }
    memcpy(Sub,new_Sub,sizeof(new_Sub));
    len = new_len;
    for(int i = 1;i <= len;i++){
        if(a.first <= Sub[i].first && Sub[i].second <= a.second){
            sort(Sub + 1,Sub + 1 + len);
            return ;
        }
    }
    Sub[++len] = a;
    sort(Sub + 1,Sub + 1 + len);
    change = 1;
}
int solve(int N,int K){
    for(int i = 1;i <= len;i++){
        dp[0][i] = -(1 << 28);
    }
    for(int j = 1;j <= K;j++){
        int last = 0;
        stq = 0;drq = -1;
        D[++drq] = {0,Sub[1].second};
        for(int i = 1;i <= len;i++){
            while(Sub[i].first >= Sub[last + 1].second){
                last++;///primul care > 0
            }
            dp[j][i] = (last ? pref_max[j - 1][last - 1] : - (1 << 28));
            while(stq <= drq && D[stq].first < last){
                stq++;
            }
            if(stq <= drq){
                dp[j][i] = max(dp[j][i],D[stq].second - Sub[i].first);
            }
            pref_max[j][i] = max(pref_max[j][i - 1],dp[j][i]);
            int cost = dp[j - 1][i] + Sub[i + 1].second;
            while(stq <= drq && D[drq].second  <= cost){
                drq--;
            }
            D[++drq] = {i,cost};
        }
    }
    return dp[K][len];
}
int main(){
    fscanf(f,"%d %d",&N,&K);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d %d",&V[i].first,&V[i].second);
    }
    sort(V + 1,V + 1 + N,cmp);
    for(int i = 1;i < N - K + 1;i++){
        baga(V[i]);
    }
    for(int i = N - K + 1;i <= N;i++){
        baga(V[i]);
        sol[i - N + K] = (change ? solve(i,i - N + K) : sol[i - N + K - 1]);
    }
    int bonus = 0,best = -(1 << 28);
    while(K){///solve(N - K + 1,1)
        best = max(best,bonus + sol[K]);
        bonus += V[N].second - V[N].first;
        N--;
        K--;
    }
    fprintf(g,"%d",best);
    fclose(f);
    fclose(g);
    return 0;
}
