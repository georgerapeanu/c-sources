#include <bits/stdc++.h>

using namespace std;

vector<int> groups(1,0);
int n,val;
int dp[82][82][80 * 79 / 2 + 5];
int cnt0 = 0;
int op = 0;

void update(int i,int s,int k,int b){
    if(0 <= i && i < n && 0 <= s && s <= cnt0 && 0 <= k && k <= op){
        dp[i][s][k] = min(dp[i][s][k],b);
    }
}

int main(){


    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&val);
        if(val == 1){
            groups.push_back(0);
        }
        else{
            groups.back()++;
            cnt0++;
        }
    }

    op = n * (n - 1) / 2;
    n = groups.size();
    vector<int> pref(n,0);
    pref[0] = groups[0];

    for(int i = 1;i < n;i++){
        pref[i] = pref[i - 1] + groups[i];
    }

    for(int i = 0;i < n;i++){
        for(int s = 0;s <= cnt0;s++){
            for(int k = 0;k <= op;k++){
                dp[i][s][k] = 1e9;
            }
        }
    }

    for(int h = 0;h <= cnt0;h++){
        dp[0][h][abs(groups[0] - h)] = h * h; 
    }

    for(int s = 0;s <= cnt0;s++){
        for(int k = 0;k <= op;k++){
            update(0,s,k + 1,dp[0][s][k]);
        }
    }

    for(int i = 0;i < n - 1;i++){
        for(int s = 0;s <= cnt0;s++){
            for(int k = 0;k <= op;k++){
                update(i,s,k + 1,dp[i][s][k]);
                for(int h = 0;s + h <= cnt0;h++){
                    update(i + 1,s + h,k + abs(h - (groups[i + 1] - (s - pref[i]))),dp[i][s][k] + h * h);
                }
            }
        }
    }

    for(int k = 0;k <= op;k++){
        printf("%d ",(cnt0 * cnt0 - dp[n - 1][cnt0][k]) / 2);
    }

    return 0;
}
