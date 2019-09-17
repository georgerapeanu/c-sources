#include <cstdio>

using namespace std;

FILE *f1 = fopen("arb4.out","r");
FILE *f2 = fopen("arb4.ok","r");

int main() {

    int a,b,id = 0;;

    while(fscanf(f1,"%d",&a) == 1 && fscanf(f2,"%d",&b) == 1) {
        ++id;
        if(a != b) {
            printf("WA on %d\n",id);
            while(true);
        }
    }

    printf("OK\n");

    fclose(f1);
    fclose(f2);

    return 0;
}
