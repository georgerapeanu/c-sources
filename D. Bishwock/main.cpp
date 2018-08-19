#include <iostream>
#include <vector>

using namespace std;

char pattern[4][2][2];
string S[3];

bool can_put_pattern(int id,int mask,int i){
    int pat_mask = (pattern[id][0][1] == 'X') + 2 * (pattern[id][1][1] == 'X');
    int cur_mask = (S[1][i] == 'X') + 2 * (S[2][i] == 'X');
    if((cur_mask & mask) != cur_mask)return 0;
    if((cur_mask & pat_mask) != 0)return 0;
    if((pat_mask & mask) != pat_mask)return 0;
    return 1;
}

int dp[105][4];

int best_for_pattern(int id,int msk,int i){
    int base_mask = (pattern[id][0][0] == 'X') + 2 * (pattern[id][1][0] == 'X');
    base_mask ^= 3;
    int ans = 0;
    for(int mask = 0;mask < 4;mask++){
        if((mask & base_mask) == mask){
            ans = max(ans,dp[i - 1][mask] + 1);
        }
    }
    return ans;
}

int main(){
    for(int i = 2;i <= 100;i++){
        dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = -(1 << 30);
    }
    pattern[0][0][0] = '.';pattern[0][0][1] = 'X';pattern[0][1][0] = 'X';pattern[0][1][1] = 'X';
    pattern[1][0][0] = 'X';pattern[1][0][1] = '.';pattern[1][1][0] = 'X';pattern[1][1][1] = 'X';
    pattern[2][0][0] = 'X';pattern[2][0][1] = 'X';pattern[2][1][0] = '.';pattern[2][1][1] = 'X';
    pattern[3][0][0] = 'X';pattern[3][0][1] = 'X';pattern[3][1][0] = 'X';pattern[3][1][1] = '.';
    cin >> S[1];S[1] = " " + S[1];
    cin >> S[2];S[2] = " " + S[2];

    for(int i = 2;i < (int)S[1].size();i++){
        for(int msk = 0;msk < 4;msk++){
            if((((S[1][i] == 'X') + 2 * (S[2][i] == 'X')) & msk) == ((S[1][i] == 'X') + 2 * (S[2][i] == 'X'))){
                dp[i][msk] = max(max(dp[i - 1][0],dp[i - 1][1]),max(dp[i - 1][2],dp[i - 1][3]));
                for(int k = 0;k < 4;k++){
                    if(can_put_pattern(k,msk,i)){
                        dp[i][msk] = max(dp[i][msk],best_for_pattern(k,msk,i));
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int k = 0;k < 4;k++){
        ans = max(ans,dp[S[1].size() - 1][k]);
    }
    cout << ans;
    return 0;
}
