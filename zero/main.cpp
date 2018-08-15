#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

FILE *f = fopen("zero.in","r");
FILE *g = fopen("zero.out","w");

int L,B,P,Q;

const int LEN = 1e3,BASE = 1e3;

void init(int A[],int val){
    A[0] = 0;
    while(val){
        A[++A[0]] = val;
        val /= BASE;
    }
    A[0] = max(A[0],1);
}

void add(int A[],int B[]){
    int t = 0;
    for(int i = 1;i <= A[0] || i <= B[0] || t;i++){
        A[i] = (i <= A[0] ? A[i] : 0) + (i <= B[0] ? B[i] : 0) + t;
        t = 0;
        if(A[i] >= BASE){
            A[i] -= BASE;
            t = 1;
        }
        A[0] = max(A[0],i);
    }
}

void scad(int A[],int B[]){
    for(int i = 1;i <= A[0];i++){
        A[i] -= B[i];
        if(A[i] < 0){
            A[i + 1]--;
            A[i] += BASE;
        }
    }
    while(A[0] > 1 && A[A[0]] == 0){
        A[0]--;
    }
}

int C[LEN];
void mult(int A[],int B[]){
    memset(C,0,sizeof(C));
    C[0] = A[0] + B[0] - 1;
    for(int i = 1;i <= A[0];i++){
        for(int j = 1;j <= B[0];j++){
            C[i + j - 1] += A[i] * B[j];
        }
    }
    int t = 0;
    for(int i = 1;i <= C[0] || t;i++){
        C[i] += t;
        t = C[i] / BASE;
        C[i] %= BASE;
        C[0] = max(C[0],i);
    }
    memcpy(A,C,sizeof(C));
}

void afis(int A[]){
    fprintf(g,"%d",A[A[0]]);
    for(int i = A[0] - 1;i > 0;i--){
        int cb = BASE / 10;
        while(cb > 1 && cb > A[i]){
            fputc('0',g);
            cb /= 10;
        }
        fprintf(g,"%d",A[i]);
    }
    fputc('\n',g);
}

int dp[22][LEN];
int SP[22][LEN];
int tmp[LEN];
int tmp2[LEN];
int baza[LEN];
int main(){

    fscanf(f,"%d %d %d %d",&L,&B,&P,&Q);

    init(tmp,B - 1);
    init(tmp2,1);
    init(baza,B);
    init(dp[0],1);
    init(SP[0],1);
    for(int i = 1;i <= L;i++){
        memcpy(dp[i],SP[i - 1],sizeof(SP[i - 1]));
        if(i - P - 2 >= 0){
            scad(dp[i],SP[i - P - 2]);
        }
        mult(dp[i],tmp);
        if(i <= P){
            add(dp[i],dp[0]);
        }
        add(SP[i],dp[i]);
        add(SP[i],SP[i - 1]);
    }
    mult(dp[L - 1],tmp);
    afis(dp[L - 1]);

    memset(dp,0,sizeof(dp));
    memset(SP,0,sizeof(SP));

    P = Q - 1;

    if(P >= 0){
        init(dp[0],1);
        init(SP[0],1);
        for(int i = 1;i <= L;i++){
            memcpy(dp[i],SP[i - 1],sizeof(SP[i - 1]));
            if(i - P - 2 >= 0){
                scad(dp[i],SP[i - P - 2]);
            }
            mult(dp[i],tmp);
            if(i <= P){
                add(dp[i],dp[0]);
            }
            add(SP[i],dp[i]);
            add(SP[i],SP[i - 1]);
        }

        for(int i = 1;i <= L - 1;i++){
            mult(tmp2,baza);
        }

        scad(tmp2,dp[L - 1]);
        mult(tmp2,tmp);
        afis(tmp2);

    }

    fclose(f);
    fclose(g);

    return 0;
}
