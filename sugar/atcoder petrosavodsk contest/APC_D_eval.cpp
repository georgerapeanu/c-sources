#include <cstdio>
#include <cstdlib>

using namespace std;

FILE *f = fopen("in","r");
FILE *g1 = fopen("out","r");
FILE *g2 = fopen("ok","r");

int main() {

    int n;

    fscanf(f,"%d",&n);
    fscanf(f,"%d",&n);

    for(int i = 0; i < n; i++) {
        int x,y;
        fscanf(g1,"%d",&x);
        fscanf(g2,"%d",&y);
        if(x != y) {
            printf("WA on line %d\n",i + 1);
            while(1);
        }
    }

    printf("OK\n");

    return 0;
}