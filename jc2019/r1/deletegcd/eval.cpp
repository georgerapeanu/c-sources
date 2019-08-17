#include <cstdio>

using namespace std;

const int QMAX = 1e6;

FILE *f1 = fopen("deletegcd.out","r");
FILE *f2 = fopen("deletegcd.ok","r");

char a[QMAX + 5];
char b[QMAX + 5];

int main() {

    fgets(a + 1,QMAX + 5,f1);
    fgets(b + 1,QMAX + 5,f2);

    for(int i = 1; '0' <= a[i] && a[i] <= '1'; i++) {
        if(a[i] != b[i]) {
            printf("WA on query %d\n",i);
            while(true);
        }
    }

    printf("OK\n");

    fclose(f1);
    fclose(f2);

    return 0;
}

