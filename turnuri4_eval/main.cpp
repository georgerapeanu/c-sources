#include <cstdio>

using namespace std;

FILE *f1 = fopen("turnuri4.ok","r");
FILE *f2 = fopen("turnuri4.out","r");

int main(){

    long long a,b;

    while(fscanf(f1,"%lld",&a) == 1 && fscanf(f2,"%lld",&b) == 1){
        if(a != b){
            printf("WA\n");
            while(1);
        }
    }
    printf("OK\n");
    return 0;
}
