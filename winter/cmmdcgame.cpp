#include <cstdio>
#include <iostream>

using namespace std;

FILE *f = fopen("cmmdcgame.in","r");
FILE *g = fopen("cmmdcgame.out","w");

const int NMAX = 3e5;
int sg[NMAX + 5];

///OEIS A055396
/*
const int NMAX = 100;
int gcd(int a,int b){
    if(b == 0){
        return a;
    }
    return gcd(b,a % b);
}

int fr[NMAX + 5];

void reset_mex(){
    for(int i = 0;i <= NMAX;i++){
        fr[i] = 0;
    }
}

int get_mex(){
    for(int i = 0;i <= NMAX;i++){
        if(fr[i] == 0){
            return i;
        }
    }
    return NMAX + 1;
}
*/
int main(){

    int cnt_prime = 0;
    for(int i = 2;i <= NMAX;i++){
        if(sg[i] == 0){
            cnt_prime++;
            for(int j = i;j <= NMAX;j += i){
                if(sg[j] == 0){
                    sg[j] = cnt_prime;
                }
            }
        }
    }

    int t;
    int n;
   
    fscanf(f,"%d",&t);

    while(t--){
        fscanf(f,"%d",&n);
        int xo = 0;

        for(int i = 1;i <= n;i++){
            int val;
            fscanf(f,"%d",&val);
            xo ^= sg[val];
        }
        fprintf(g,(xo == 0 ? "J\n":"D\n"));
    }

    fclose(f);
    fclose(g);

    return 0;
}
