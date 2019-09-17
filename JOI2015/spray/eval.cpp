#include <cstdio>

using namespace std;

int main() {

    FILE *f1 = fopen("out","r");
    FILE *f2 = fopen("ok","r");

    int a,b;
    int cnt = 0;
    while(fscanf(f1,"%d",&a) == 1 && fscanf(f2,"%d",&b) == 1) {
        cnt++;
        if(a != b) {
            printf("WA on %d\n",cnt);
            while(true);
        }
    }

    printf("Ok\n");

    return 0;
}
