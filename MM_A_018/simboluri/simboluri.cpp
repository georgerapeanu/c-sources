#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

FILE *f = fopen("simboluri.in","r");
FILE *g = fopen("simboluri.out","w");

const int NMAX = 1e5;
const int SIGMA = 10;

int q;
int phi[9 * NMAX + 5];

int gcd(int a,int b){
    if(!b){
        return a;
    }
    return gcd(b,a % b);
}

int cf1[9 * NMAX + 5];
int cf2[9 * NMAX + 5];
int l1[9 * NMAX + 5];
int l2[9 * NMAX + 5];
int e2[9 * NMAX + 5];
int e5[9 * NMAX + 5];
int red[9 * NMAX + 5];

void afis(int n){
    for(int i = 1;i <= l1[n];i++){
        fprintf(g,"%d",cf1[n]);
    }
    for(int i = 1;i <= l2[n];i++){
        fprintf(g,"%d",cf2[n]);
    }
    fprintf(g,"\n");
}

int main(){

    for(int i = 2;i <= NMAX;i++){
        phi[i] = i;
    }

    for(int i = 2;i <= 9 * NMAX;i++){
        e2[i] = e2[i / 2];
        e5[i] = e5[i / 5]; 
        red[i] = i;
        if(i % 2 == 0){
            e2[i]++;
            red[i] = red[i / 2];
        }
        if(i % 5 == 0){
            e5[i]++;
            red[i] = red[i / 5];
        }
        if(phi[i] != i){
            continue;
        }
        for(int j = i;j <= 9 * NMAX;j += i){
            phi[j] = (phi[j] / i) * (i - 1);
        }
    }

    for(int n = 1;n <= NMAX;n++){
        int tmp = gcd(n,10);
        if(tmp == 1){
            cf1[n] = 9;l1[n] = max(phi[n],1);
            cf2[n] = 0;l2[n] = 0;
        }
        else if(tmp == 2 && n % 16 != 0){
            cf1[n] = gcd(n,16);l1[n] = max(phi[9 * n / cf1[n]],1);
            cf2[n] = 0;l2[n] = 0;
        }
        else if(tmp == 5 && n % 25 != 0){
            cf1[n] = 5;l1[n] = max(phi[9 * n / 5],1);
            cf2[n] = 0;l2[n] = 0;
        }
        else{
            cf1[n] = 9;l1[n] = phi[red[n]];
            cf2[n] = 0;l2[n] = max(e2[n],e5[n]);
        }
    }

    fscanf(f,"%d",&q);

    int n;

    while(q--){
        fscanf(f,"%d",&n);
        afis(n);
    }

    fclose(f);
    fclose(g);

    return 0;
}
