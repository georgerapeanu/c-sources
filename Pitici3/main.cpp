#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("pitici3.in","r");
FILE *g = fopen("pitici3.out","w");
int dp[2005][2005];
pair<int,int> P[2005];
int N,D;
int S[2005];
bool cmp(pair<int,int> a,pair<int,int> b){
    return a.first + a.second < b.first + b.second;
}
int main(){
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d %d",&P[i].first,&P[i].second);
    }
    fscanf(f,"%d",&D);
    sort(P + 1,P + 1 + N,cmp);
    for(int i = N;i;i--){
        S[i] = P[i].first + S[i + 1];
    }
    for(int i = 0;i <= N;i++){
        dp[0][0] = 0;
        for(int j = 0;j <= N;j++){
            if(i == 0 || j > i){
                dp[i][j] = -(1 << 28);
            }
            else{
                dp[i][j] = dp[i - 1][j] + P[i].first;
                if(j && S[i] + P[i].second + dp[i - 1][j - 1] >= D){
                    dp[i][j] = max(dp[i][j],dp[i - 1][j - 1]);
                }
            }
        }
    }
    int best = N;
    while(dp[N][best] < 0){
        best--;
    }
    fprintf(g,"%d",best);
    fclose(f);
    fclose(g);
    return 0;
}
