#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }

    return a;
}

int n;
string s;
int pw2[200005];
int sum[200005];

int get_pw2(int x){
    if(x <= 0){
        return 1;
    }
    return pw2[x];
}

int get_sum(int x){
    if(x < 0){
        return 0;
    }
    return sum[x];
}

int main(){

    freopen("bignum.in","r",stdin);
    freopen("bignum.out","w",stdout);

    pw2[0] = 1;
    sum[0] = 1;

    for(int i = 1;i <= 200000;i++){
        pw2[i] = add(pw2[i - 1],pw2[i - 1]);
        sum[i] = mult(3,sum[i - 1]);
    }

    for(int i = 0;i <= 200000;i++){
        sum[i] = scad(sum[i],pw2[i]);
    }
   
    cin >> s;
    
    n = s.size();
    s = " " + s;

    int cnt_1 = 0;

    int ans = 0;

    for(int i = 1;i <= n + 1;i++){
        if(i > n || s[i] == '1'){
            ans = add(ans,add(mult(scad(get_pw2(cnt_1),1),get_pw2(n - i)),mult(get_pw2(cnt_1),get_sum(n - i))));

            cnt_1++;
        }
    }
   
    cout << ans << endl;

    return 0;
}
