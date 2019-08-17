#include <cstdio>

using namespace std;

FILE *f = fopen("ultrapoligon.in","r");
FILE *g = fopen("ultrapoligon.out","w");

const int MOD = 1e9 + 7;
const int NMAX = 1e5;

int n;
int x[NMAX + 5];
int y[NMAX + 5];
int weighted_sum_x[NMAX + 5];
int weighted_sum_y[NMAX + 5];

inline int add(int a,int b) {
    a += b;
    if(a >= MOD) {
        a -= MOD;
    }
    return a;
}

inline int scad(int a,int b) {
    a -= b;
    if(a < 0) {
        a += MOD;
    }
    return a;
}

inline int mult(int a,int b) {
    return 1LL * a * b % MOD;
}

int main() {

    fscanf(f,"%d",&n);

    int doilanm2 = 1;
    const int inv2 = 500000004;

    for(int i = 1; i <= n - 2; i++) {
        doilanm2 = add(doilanm2,doilanm2);
    }

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d %d",&x[i],&y[i]);
    }

    int upper_sum_x = 0;
    int upper_sum_y = 0;

    for(int i = n; i; i--) {
        weighted_sum_x[i] = scad(weighted_sum_x[i],upper_sum_x);
        weighted_sum_y[i] = scad(weighted_sum_y[i],upper_sum_y);
        upper_sum_x = add(mult(2,upper_sum_x),x[i]);
        upper_sum_y = add(mult(2,upper_sum_y),y[i]);
    }

    int under_sum_x = 0;
    int under_sum_y = 0;

    for(int i = n; i; i--) {
        weighted_sum_x[i] = add(weighted_sum_x[i],under_sum_x);
        weighted_sum_y[i] = add(weighted_sum_y[i],under_sum_y);
        under_sum_x = add(mult(inv2,under_sum_x),mult(x[i],doilanm2));
        under_sum_y = add(mult(inv2,under_sum_y),mult(y[i],doilanm2));
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        ans = add(ans,scad(mult(x[i],weighted_sum_y[i]),mult(y[i],weighted_sum_x[i])));
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
