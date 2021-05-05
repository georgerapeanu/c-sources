#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int n;
string s[155];

int dp[155][155][155][4];
int sum[155][155][4];

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

void make_sum(int x,int y,int conf,int value){
    sum[x][y][conf] = scad(add(value,add(sum[x - 1][y][conf],sum[x][y - 1][conf])),sum[x - 1][y - 1][conf]);
}

int get_sum(int x,int xx,int y,int yy,int conf){
    x = max(x,1);
    xx = min(xx,n);
    y = max(y,1);
    yy = min(yy,n);
    if(x > xx || y > yy){
        return 0; 
    }

    int ans = scad(add(sum[xx][yy][conf],sum[x - 1][y - 1][conf]),add(sum[xx][y - 1][conf],sum[x - 1][yy][conf]));

    return ans;
}

int main(){

    cin >> n;

    for(int i = 1;i <= n;i++){
        cin >> s[i];
        s[i] = " " + s[i];
    }

    int ans = 0;
    for(int j = 1;j <= n;j++){
        for(int l = 1;l <= n;l++){
            for(int r = 1;r <= n;r++){
                for(int conf = 0;conf < 4;conf++){
                    make_sum(l,r,conf,dp[j - 1][l][r][conf]);
                }
            }
        }
        for(int l = 1;l <= n;l++){
            bool ok = true;
            for(int r = l;r <= n;r++){
                ok &= (s[r][j] == 'G');
                if(ok == false){
                    break;
                }

                dp[j][l][r][0] = get_sum(l,n,1,r,0);
                dp[j][l][r][1] = add(get_sum(1,l - 1,l,r,0),get_sum(1,l,l,r,1));
                dp[j][l][r][2] = add(get_sum(l,r,r + 1,n,0),get_sum(l,r,r,n,2));
                dp[j][l][r][3] = add(add(get_sum(1,l - 1,r + 1,n,0),get_sum(1,l,r + 1,n,1)),add(get_sum(1,l - 1,r,n,2),get_sum(1,l,r,n,3)));
                dp[j][l][r][0] = add(dp[j][l][r][0],1);

                for(int conf = 0;conf < 4;conf++){
                    ans = add(ans,dp[j][l][r][conf]);
                }
            }
        }
    }
   

    printf("%d\n",ans);

    return 0;
}
