#include <cstdio>

using namespace std;

FILE *f1 = fopen("palatulvoltaic.out","r");
FILE *f2 = fopen("palatulvoltaic.ok","r");

int main() {

    int a,b;

    while(fscanf(f1,"%d",&a) == 1 && fscanf(f2,"%d",&b) == 1) {
        if(a != b) {
            printf("WA\n");
            while(true);
        }
    }
    printf("OK\n");

    fclose(f1);
    fclose(f2);
    return 0;
}
