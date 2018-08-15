#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("siruri.in","r");
FILE *g = fopen("siruri.out","w");

int N,A[100005];
int M,B[100005];

const int LEN = 1e4;
char buff[LEN];
int ind = LEN - 1;
int i32(){
    while(buff[ind] != '-' && ('0' > buff[ind] || '9' < buff[ind])){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    int rez = 0,sgn = 1;
    if(buff[ind] == '-'){
        sgn = -1;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    while(buff[ind] >= '0' && buff[ind] <= '9'){
        rez = rez * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return rez * sgn;
}

int S, D;
const int MOD = 666013;
const int BASE = 381001;
int hsh[MOD];
int pw[100005];

bool check(int st,int dr,int len){
    for(int i = 0;i < len;i++){
        if(A[st + i] != B[dr + i]){
            return 0;
        }
    }
    return 1;
}

bool ok(int len){
    memset(hsh,0,sizeof(hsh));
    int h = 0;
    for(int i = 1;i <= N;i++){
        h = (1LL * h * BASE + (A[i] + BASE / 2)) % MOD;
        if(i > len){
            h = (h - 1LL * pw[len] * (A[i - len] + BASE / 2)) % MOD;
            if(h < 0){
                h += MOD;
            }
        }
        if(i >= len){
            hsh[h] = i - len + 1;
        }
    }

    h = 0;
    for(int i = 1;i <= M;i++){
        h = (1LL * h * BASE + (B[i] + BASE / 2)) % MOD;
        if(i > len){
            h = (h - 1LL * pw[len] * (B[i - len] + BASE / 2)) % MOD;
            if(h < 0){
                h += MOD;
            }
        }
        if(i >= len && hsh[h]){
            if(check(hsh[h],i - len + 1,len)){
                S = hsh[h];
                D = i - len + 1;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    N = i32();
    for(int i = 1;i <= N;i++){
        A[i] = i32();
    }
    M = i32();
    for(int i = 1;i <= M;i++){
        B[i] = i32();
    }

    for(int i = 1;i < N;i++){
        A[i] = A[i] - A[i + 1];
    }
    N--;
    for(int i = 1;i < M;i++){
        B[i] = B[i + 1] - B[i];
    }
    M--;

    pw[0] = 1;
    for(int i = 1;i <= 100000;i++){
        pw[i] = 1LL * pw[i - 1] * BASE % MOD;
    }

    int st = 0,dr = max(N,M) + 5;
    while(dr - st > 1){
        int mid = (st + dr) / 2;
        if(ok(mid)){
            st = mid;
        }
        else{
            dr = mid;
        }
    }
    ok(st);

    fprintf(g,"%d %d %d\n",st + 1,S,D);

    fclose(f);
    fclose(g);

    return 0;
}
