#include <cstdio>
#include <vector>
	
using namespace std;
	
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int NMAX = 5e5;
const int LGMAX = 19;
 
int pw1[NMAX + 5];
int pw2[NMAX + 5];
 
FILE *f = fopen("brperm.in","r");
FILE *g = fopen("brperm.out","w");
 
int n,q;
char s[NMAX + 5];
 
int initial[LGMAX + 1][NMAX + 1][2];
int dp[LGMAX + 1][NMAX + 1][2];
int base[LGMAX + 1][2];
int inv_base[LGMAX + 1][2];

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

void str(char *ans){
    ind = 0;
    while(buff[ind] < 'a' || buff[ind] > 'z'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    while(!(buff[ind] < 'a' || buff[ind] > 'z')){
        *ans = buff[ind];
        ans++;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
}

int i32(){
    int ans = 0;
    
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}
 
int main(){
 
    base[0][0] = inv_base[0][0] = 1;
    base[0][1] = inv_base[0][1] = 1;
    base[1][0] = 31;inv_base[1][0] = 129032259;
    base[1][1] = 31;inv_base[1][1] = 838709685;

    for(int i = 2;i <= LGMAX;i++){
        base[i][0] = 1LL * base[i  - 1][0] * base[i - 1][0] % MOD1;
        base[i][1] = 1LL * base[i  - 1][1] * base[i - 1][1] % MOD2;
        inv_base[i][0] = 1LL * inv_base[i  - 1][0] * inv_base[i - 1][0] % MOD1;
        inv_base[i][1] = 1LL * inv_base[i  - 1][1] * inv_base[i - 1][1] % MOD2;
    }
 
    n = i32();
    str(s + 1);

    for(int i = 1;i <= n;i++){
        dp[0][i][0] = s[i] - 'a' + 1;
        dp[0][i][1] = s[i] - 'a' + 1;
        initial[0][i][0] = s[i] - 'a' + 1;
        initial[0][i][1] = s[i] - 'a' + 1;
    }

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= n - (1 << h) + 1;i++){
            dp[h][i][0] = (1LL * dp[h - 1][i][0] * base[LGMAX - h][0] + dp[h - 1][i + (1 << (h - 1))][0]) % MOD1;
            dp[h][i][1] = (1LL * dp[h - 1][i][1] * base[LGMAX - h][1] + dp[h - 1][i + (1 << (h - 1))][1]) % MOD2;
        }
    }

    for(int h = 1;(1 << h) <= n;h++){
        int hsh[2] = {0,0};
        int top[2] = {1,1};
        for(int i = 1;i < (1 << h);i++){
            top[0] = 1LL * top[0] * base[LGMAX - h][0] % MOD1;
            top[1] = 1LL * top[1] * base[LGMAX - h][1] % MOD2;
        }
        for(int i = n - (1 << h) + 1;i <= n;i++){
            hsh[0] = (1LL * hsh[0] * base[LGMAX - h][0] + s[i] - 'a' + 1) % MOD1;
            hsh[1] = (1LL * hsh[1] * base[LGMAX - h][1] + s[i] - 'a' + 1) % MOD2;
        }
        for(int i = n - (1 << h) + 1;i;i--){
            initial[h][i][0] = hsh[0];
            initial[h][i][1] = hsh[1];
            hsh[0] = (MOD1 + hsh[0] - (s[i + (1 << h) - 1] - 'a' + 1)) % MOD1;
            hsh[1] = (MOD2 + hsh[1] - (s[i + (1 << h) - 1] - 'a' + 1)) % MOD2;
            hsh[0] = 1LL * hsh[0] * inv_base[LGMAX - h][0] % MOD1;
            hsh[1] = 1LL * hsh[1] * inv_base[LGMAX - h][1] % MOD2;
            hsh[0] = (1LL * (s[i - 1] - 'a' + 1) * top[0] + hsh[0]) % MOD1;
            hsh[1] = (1LL * (s[i - 1] - 'a' + 1) * top[1] + hsh[1]) % MOD2;
        }
    }

    q = i32();
    
    while(q--){
        int pos,k;
        pos = i32();k = i32();
        pos++;
        if(pos + (1 << k) - 1 > n){
            fprintf(g,"0\n");
            continue;
        }
        fprintf(g,"%d\n",int(dp[k][pos][0] == initial[k][pos][0] && dp[k][pos][1] == initial[k][pos][1]));
    }
 
    fclose(f);
    fclose(g);
 
    return 0;
}
