#include <cstdio>

using namespace std;

FILE *f1 = fopen("overpower.out","r");
FILE *f2 = fopen("overpower.ok","r");

int main() {

    long long a,b;

    int id = 0;

    while(fscanf(f1,"%lld",&a) == 1 && fscanf(f2,"%lld",&b) == 1) {
        id++;
        if(a != b) {
            printf("WA on line %d\n",id);
            while(true);
        }
    }

    printf("OK\n");

    fclose(f1);
    fclose(f2);

    return 0;
}
