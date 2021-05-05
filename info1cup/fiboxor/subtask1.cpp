#include <cstdio>

using namespace std;

FILE *f = fopen("xorfibo.in","r");
FILE *g = fopen("xorfibo.out","w");

int main() {

    int q;
    
    fscanf(f,"%d",&q);

    while(q--) {
        int k;
        long long l,r;
        fscanf(f,"%d %lld %lld",&k,&l,&r);
        l--;

        l %= 3;
        r %= 3;


        fprintf(g,"%d\n",(l == 1) ^ (r == 1));
    }

    fclose(f);
    fclose(g);

    return 0;
}
