#include <cstdio>

using namespace std;

FILE *f1 = fopen("out1","r");
FILE *f2 = fopen("out2","r");

int main() {
    long long a,b;
    fscanf(f1,"%lld",&a);
    fscanf(f2,"%lld",&b);

    if(a != b) {
        printf("WA\n");
        while(true);
    }

    printf("OK\n");
    return 0;
}
