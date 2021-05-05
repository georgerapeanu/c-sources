#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int n;
string s[155];

int dp_left[155][155][155];
int dp_right[155][155][155];
bool is_ok[155][155][155];
int sum[155][155];

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


int main(){

    cin >> n;

    for(int i = 1;i <= n;i++){
        cin >> s[i];
        s[i] = " " + s[i];
    }

    for(int j = 1;j <= n;j++){
        for(int i = 1;i <= n;i++){
            int pref_sum = 0;
            for(int h = 1;h <= n;h++){
                pref_sum = add(pref_sum,dp_left[i][j - 1][h]);
                sum[i][h] = add(pref_sum,sum[i - 1][h - 1]);
            }
        }
        for(int i = 1;i <= n;i++){
            bool ok = true;
            for(int h = 1;h <= n;h++){
                ok &= (h <= i && s[i - h + 1][j] == 'G');
                if(ok == false){
                    break;
                }
                is_ok[i][j][h] = true;
                dp_left[i][j][h] = add(1,sum[i][h]);
            }
        }
    }
    
    for(int j = n;j >= 1;j--){
        for(int i = 1;i <= n;i++){
            int pref_sum = 0;
            for(int h = 1;h <= n;h++){
                pref_sum = add(pref_sum,dp_right[i][j + 1][h]);
                sum[i][h] = add(pref_sum,sum[i - 1][h - 1]);
            }
        }
        for(int i = 1;i <= n;i++){
            bool ok = true;
            for(int h = 1;h <= n;h++){
                ok &= (h <= i && s[i - h + 1][j] == 'G');
                if(ok == false){
                    break;
                }
                dp_right[i][j][h] = add(1,sum[i][h]);
            }
        }
    }

    int ans = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            for(int h = 1;h <= i;h++){
                if(is_ok[i][j][h]){
                    printf("deb %d %d %d is %d %d %d\n",i,j,h,dp_left[i][j][h],dp_right[i][j][h],mult(dp_left[i][j][h],scad(dp_right[i][j][h],dp_right[i][j + 1][h])));
                    ans = add(ans,mult(dp_left[i][j][h],scad(dp_right[i][j][h],dp_right[i][j + 1][h])));
                }
            }
        }
    }

    printf("%d\n",ans);

    return 0;
}
