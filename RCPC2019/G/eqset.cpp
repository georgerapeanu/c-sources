#include <cstdio>

using namespace std;

FILE *f = fopen("eqset.in","r");
FILE *g = fopen("eqset.out","w");

long long gcd(long long a,long long b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

bool full_contain(long long x,long long a) {
    while(a != 1) {
        x /= a;
        a = gcd(a,x);
    }
    return (x == 1);
}

int main() {

    int t;

    fscanf(f,"%d",&t);

    while(t--) {
        long long x,y;
        fscanf(f,"%lld %lld",&x,&y);
        long long a = gcd(x,y);
        if(full_contain(x,a) && full_contain(y,a)) {
            fprintf(g,"1\n");
        }
        else {
            fprintf(g,"0\n");
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
