#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("tort.in","r");
FILE *g = fopen("tort.out","w");

long long A,B;

const int LEN = 100,BASE = 1e4;

long long FSTA[LEN],FSTB[LEN];
long long SNDA[LEN],SNDB[LEN];
long long LSTA[LEN],LSTB[LEN];

void init(long long A[],int val){
    A[0] = 0;
    while(val){
        A[++A[0]] = val % BASE;
        val /= BASE;
    }
    A[0] = max(A[0],1LL);
}

void add(long long A[],long long B[]){
    int t = 0;
    for(int i = 1;i <= A[0] || i <= B[0] || t;i++){
        A[i] += B[i] + t;
        t = 0;
        if(A[i] >= BASE){
            A[i] -= BASE;
            t++;
        }
        A[0] = max(A[0],(long long)i);
    }
}

void scad(long long A[],long long B[]){
    for(int i = 1;i <= B[0];i++){
        A[i] -= B[i];
        if(A[i] < 0){
            A[i] += BASE;
            A[i + 1]--;
        }
    }
    while(A[0] > 1 && !A[A[0]]){
        A[0]--;
    }
}

long long C[LEN];
void mult(long long A[],long long B[]){
    memset(C,0,sizeof(C));
    C[0] = A[0] + B[0] - 1;
    for(int i = 1;i <= A[0];i++){
        for(int j = 1;j <= B[0];j++){
            C[i + j - 1] += A[i] * B[j];
        }
    }
    long long t = 0;
    for(int i = 1;i <= C[0] || t;i++){
        C[i] += t;
        t = C[i] / BASE;
        C[i] %= BASE;
        C[0] = max(C[0],(long long)i);
    }
    memcpy(A,C,sizeof(C));
}

void baga(long long MA[],long long AUX[],int a,int b,int c){
    if(a % 2){
        b /= 2;
    }
    else{
        a /= 2;
    }
    init(MA,a);
    init(AUX,b);
    mult(MA,AUX);
    init(AUX,c);
    mult(MA,AUX);
}

int main(){

    fscanf(f,"%lld %lld",&A,&B);

    baga(FSTA,FSTB,A + 2,A + 1,B + 1);
    baga(SNDA,SNDB,B + 2,B + 1,A + 1);
    init(LSTA,A + 1);init(LSTB,B + 1);mult(LSTA,LSTB);

    add(FSTA,SNDA);
    scad(FSTA,LSTA);

    fprintf(g,"%lld",FSTA[FSTA[0]]);
    for(int i = FSTA[0] - 1;i;i--){
        int cb = BASE / 10;
        while(cb > 1 && cb > FSTA[i]){
            cb /= 10;
            fputc('0',g);
        }
        fprintf(g,"%lld",FSTA[i]);
    }

    ///fprintf(g,"%lld",(A + 2) * (A + 1) * (B + 1) / 2 + (B + 2) * (B + 1) * (A + 1) / 2 - (A + 1) * (B + 1));

    fclose(f);
    fclose(g);

    return 0;
}
