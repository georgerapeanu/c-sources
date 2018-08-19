#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f = fopen("dif2.in","r");
FILE *g = fopen("dif2.out","w");
int N,C;
long long p1,p2;
int P[300005];
long long great(long long val){
    long long rez = 0;
    int j = N;
    for(int i = 1;i <= N;i++){
        while(1LL * P[i] * P[j] >= val){
            j--;
        }
        rez += N - j;
    }
    return rez;
}
long long fi(long long pos){
    long long st = 0,dr = 1LL << 60;
    while(dr - st > 1){
        long long mid = (st + dr) / 2;
        if(great(mid) < pos){
            dr = mid;
        }
        else {
            st = mid;
        }
    }
    return st;
}
int main(){
    fscanf(f,"%d",&C);
    fscanf(f,"%d",&N);
    if(C == 2){
        fscanf(f,"%lld %lld",&p1,&p2);
    }
    for(int i = 1;i <= N;i++){
        fscanf(f,"%d",&P[i]);
    }
    sort(P + 1,P + 1 + N);
    if(C == 1){
        fprintf(g,"%lld",fi(1) - fi(1LL * N * N));
    }
    else{
        fprintf(g,"%lld",fi(p1) - fi(p2));
    }
    fclose(f);
    fclose(g);
    return 0;
}
