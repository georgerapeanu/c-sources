#include <cstdio>

using namespace std;

FILE *f1 = fopen("dreptunghiuri.out","r");
FILE *f2 = fopen("dreptunghiuri.ok","r");

int main(){

    long long a,b;
   
    fscanf(f1,"%lld",&a);
    fscanf(f2,"%lld",&b);

    if(a != b){
        printf("WA\n");
        while(true);
    }

    printf("OK\n");

    fclose(f1);
    fclose(f2);

    return 0;
}
