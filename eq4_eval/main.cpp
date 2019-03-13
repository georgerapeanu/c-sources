#include <cstdio>
using namespace std;

FILE *f1 = fopen("eq4.out","r");
FILE *f2 = fopen("eq4.ok","r");

int main(){
    long long a,b;
    fscanf(f1,"%lld",&a);
    fscanf(f2,"%lld",&b);
    if(a != b){
        printf("WA\n");
        while(1);
    }
    printf("OK\n");
    return 0;
}
