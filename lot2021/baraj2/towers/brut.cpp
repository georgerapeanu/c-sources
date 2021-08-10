#include <bits/stdc++.h>

using namespace std;


int t;
int n,k;
int r[50];
int p[50];
int dp[50][50][50];
vector<int> ant[50][50][50];
vector<int> ans;

int main(){
    
    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&k);

        for(int i = 1;i <= k;i++){
            scanf("%d",&r[i]);
        }

        for(int i = 1;i <= n;i++){
            scanf("%d",&p[i]);
        }

        for(int i = 0;i <= n;i++){
            for(int j = 0;j <= n;j++){
                for(int l = 0;l <= n;l++){
                    dp[i][j][l] = 0;
                }
            }
        }

        p[0] = -1e8;
        dp[0][0][0] = 1;

        bool ok_last = false;

        for(int h = 1;h <= n;h++){
            for(int i = 0;i < h && (k > 0);i++){
                for(int j = 0;j < h && (k > 1);j++){
                    for(int l = 0;l < h && (k > 2);l++){
                        if(dp[i][j][l] == 0 || ((i != h - 1) && (j != h - 1) && (l != h - 1))){
                            continue;
                        }
                        if((k > 0) && p[i] + r[1] <= p[h]){
                            dp[h][j][l] = true;
                            ant[h][j][l] = {i,j,l};
                            if(h == n){
                                ans = {h,j,l};
                                ok_last = true;
                            }
                        }
                        if((k > 1) && p[j] + r[2] <= p[h]){
                            dp[i][h][l] = true;
                            ant[i][h][l] = {i,j,l};
                            if(h == n){
                                ans = {i,h,l};
                                ok_last = true;
                            }
                        }
                        if((k > 2) && p[l] + r[3] <= p[h]){
                            dp[i][j][h] = true;
                            ant[i][j][h] = {i,j,l};
                            if(h == n){
                                ok_last = true;
                                ans = {i,j,h};
                            }
                        }
                    }
                }
            }
        }

        printf("%d\n",(int)ok_last);
        if(ok_last){
        vector<vector<int> > part(k,vector<int>());

        while(ans[0] != 0 || ans[1] != 0 || ans[2] != 0){
            vector<int> pr = ant[ans[0]][ans[1]][ans[2]];
            if(pr[0] != ans[0]){
                part[0].push_back(ans[0]);
            }else if(pr[1] != ans[1]){
                part[1].push_back(ans[1]);
            }else{
                part[2].push_back(ans[2]);
            }
            ans = pr;
        }

        for(int i = 0;i < k;i++){
            reverse(part[i].begin(),part[i].end());
            for(auto it:part[i]){
                printf("%d ",it);
            }
            printf("\n");
        }
        }
    }

    return 0;
}
