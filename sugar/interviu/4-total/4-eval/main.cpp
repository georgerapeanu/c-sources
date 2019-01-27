#include <cstdio>

using namespace std;

FILE *f1 = fopen("out","r");
FILE *f2 = fopen("ok","r");

int main(){
    int a,b;

    fscanf(f1,"%d",&a);
    fscanf(f2,"%d",&b);

    if(a != b){
        printf("WA\n");
        while(1);
    }

    printf("OK\n");

    fclose(f1);
    fclose(f2);

    return 0;
}
