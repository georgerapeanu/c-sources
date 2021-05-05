#include <bits/stdc++.h>

using namespace std;

int t;
int n,q;
string s[4];
int score[4];

int cnt_total[121][121][121];
double dp[121][121][121];

int main(){

    cin >> t;

    for(int h = 1;h <= t;h++){
        
        cin >> n >> q;
        
        for(int i = 1;i <= n;i++){
            cin >> s[i];
            for(auto &it:s[i]){
                if(it == 'T'){
                    it = '1';
                }else{
                    it = '0';
                }
            }
            cin >> score[i];
        }
        for(int i = n + 1;i <= 3;i++){
            score[i] = 0;
            s[i] = string(q,'2');
        }

        cnt_total[0][0][0] = 1;
        
    }

    return 0;
}
