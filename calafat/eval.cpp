#include <cstdio>

using namespace std;

FILE *f1 = fopen("calafat.out","r");
FILE *f2 = fopen("calafat.ok","r");

int main() {

    long long a = -1,b = -2;

    int test = 0;

    while(fscanf(f1,"%lld",&a) == 1 && fscanf(f2,"%lld",&b) == 1) {
        test++;
        if(a != b) {
            printf("WA on %d %lld %lld\n",test,a,b);
            while(true);
        }
    }

    printf("OK\n");

    fclose(f1);
    fclose(f2);

    return 0;
}
