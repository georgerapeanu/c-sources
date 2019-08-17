#include <cstdio>

using namespace std;

FILE *f1 = fopen("hacker.out","r");
FILE *f2 = fopen("hacker.ok","r");

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
