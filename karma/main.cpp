#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("karma.in");
ofstream g("karma.out");
const int MOD = (1e9) + 7;
int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}
int dp[1 << 20];
int heights[1 << 20][21];
string S[21];
int N,M;
int main(){
    f >> N >> M;
    for(int i = 1;i <= N;i++){
        f >> S[i];
        S[i] = " " + S[i];
        int num = 0;
        bool ok = 1;
        for(int j = 1;j <= M;j++){
            num += (S[i][j] == '(' ? 1:-1);
        }
        ok &= (num == 0);
        if(!ok){
            g << 0;
            return 0;
        }
    }
    dp[0] = 1;
    for(int conf = 1;conf < (1 << M);conf++){
        for(int i = 0;i < M;i++){
            if((conf >> i) & 1){
                for(int j = 1;j <= N;j++){
                    heights[conf][j] += (S[j][i + 1] == '(' ? 1:-1) + heights[conf ^ (1 << i)][j];
                }
                break;
            }
        }
    }
    for(int conf = 1;conf < (1 << M);conf++){
        bool ok = 1;
        for(int i = 1;i <= N;i++){
            if(heights[conf][i] < 0){
                ok = 0;
                break;
            }
        }
        if(!ok){
            continue;
        }
        for(int i = 0;i < M;i++){
            if((conf >> i) & 1){
                int uconf = (conf ^ (1 << i));
                dp[conf] = add(dp[conf],dp[uconf]);
            }
        }
    }
    g << dp[(1 << M) - 1];
    f.close();
    g.close();
    return 0;
}
