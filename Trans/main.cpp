#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;
FILE *f = fopen("trans.in","r");
FILE *g = fopen("trans.out","w");
pair<int,int> V[16005];
long long dp[16005];
long long S0[16005];
long long S1[16005];
int Q;
int N;
int main(){
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d %d",&V[i].first,&V[i].second);
        S0[i] = S0[i - 1] + (V[i].first != 0) * V[i].second;
        S1[i] = S1[i - 1] + (V[i].first != 1) * V[i].second;
    }
    fscanf(f,"%d",&Q);
    while(Q--){
        int K,T;
        fscanf(f,"%d %d",&K,&T);
        dp[0] = 0;
        deque<int> D0,D1;
        D0.push_back(0);D1.push_back(0);
        for(int i = 1;i <= N;i++){
            while(!D0.empty() && D0.front() < i - K){
                D0.pop_front();
            }
            while(!D1.empty() && D1.front() < i - K){
                D1.pop_front();
            }
            dp[i] = min(dp[D0.front()] + T + S0[i] - S0[D0.front()],dp[D1.front()] + T + S1[i] - S1[D1.front()]);
            while(!D0.empty() && dp[i] - S0[i] < dp[D0.back()] - S0[D0.back()]){
                D0.pop_back();
            }
            while(!D1.empty() && dp[i] - S1[i] < dp[D1.back()] - S1[D1.back()]){
                D1.pop_back();
            }
            D0.push_back(i);D1.push_back(i);
        }
        fprintf(g,"%lld\n",dp[N]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
