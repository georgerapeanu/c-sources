#include <cstdio>

using namespace std;

FILE *f1 = fopen("aimin.out","r");
FILE *f2 = fopen("aimin.ok","r");

int main(){

    int a,b;
    
    fscanf(f1,"%d",&a);
    fscanf(f2,"%d",&b);

    if(a != b){
        printf("WA\n");
        while(true);
    }

    printf("OK\n");

    return 0;
}
