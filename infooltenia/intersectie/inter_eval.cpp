#include<cstdio>

using namespace std;

FILE *f1 = fopen("intersectie.out","r");
FILE *f2 = fopen("intersectie.ok","r");

int main(){

    int a,b;

    while(fscanf(f1,"%d",&a) == 1 && fscanf(f2,"%d",&b) == 1){
        if(a != b){
            printf("WA\n");

            while(1);
        }
    }

    printf("OK\n");

    return 0;
}
