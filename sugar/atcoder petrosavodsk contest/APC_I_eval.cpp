#include <cstdio>

using namespace std;

FILE *f = fopen("in","r");
FILE *g1 = fopen("out","r");
FILE *g2 = fopen("ok","r");

int main() {

    int n,q;
    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= q; i++) {
        int x,y;
        fscanf(g1,"%d",&x);
        fscanf(g2,"%d",&y);
        if(x != y) {
            printf("WA on line %d\n",i);
            fflush(stdout);
            while(1);
        }
    }

    printf("OK\n");
    fflush(stdout);

    fclose(f);
    fclose(g1);
    fclose(g2);
    return 0;
}