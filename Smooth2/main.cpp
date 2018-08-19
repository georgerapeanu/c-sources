#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
FILE *f = fopen("smooth2.in","r");
FILE *g = fopen("smooth2.out","w");
bool U[30];
bool SELECTED[30];
char C[100005];
int N,rez = 1 << 30;
int costA[30];
int costB[30];
int dp[30][30];
vector<char> Aval;
int select_chars(int SIGMA){
    memset(costA,0,sizeof(costA));
    memset(costB,0,sizeof(costB));
    for(int st = 1;st <= N;st += SIGMA){
        memset(U,0,sizeof(U));
        for(int i = st;i < st + SIGMA && i <= N;i++){
            costB[C[i] - 'a']++;
            costA[C[i] - 'a'] += (U[C[i] - 'a']);
            U[C[i] - 'a'] = 1;
        }
    }
    for(int i = 1;i < (int)Aval.size();i++){
        for(int j = 0;j <= i;j++){
            dp[i][j] = min((j == i ? 1 << 28 : dp[i - 1][j] + costB[Aval[i] - 'a']),(j > 0 ? dp[i - 1][j - 1] + costA[Aval[i] - 'a'] : 1 << 28));
        }
    }
    return dp[(int)Aval.size() - 1][min(SIGMA,(int)Aval.size() - 1)];
}
int main(){
    fgets(C + 1,100005,f);
    N = strlen(C + 1);
    N -= (C[N] == '\n');
    for(int i = 1;i <= N;i++){
        Aval.push_back(C[i]);
    }
    Aval.push_back((char)0);
    sort(Aval.begin(),Aval.end());
    Aval.resize(unique(Aval.begin(),Aval.end()) - Aval.begin());
    for(int SIGMA = 1;SIGMA <= 26;SIGMA++){
        rez = min(rez,select_chars(SIGMA));
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
