#include <cstdio>

using namespace std;

FILE *f1 = fopen("shoebox.ok","r");
FILE *f2 = fopen("shoebox.out","r");

int a,b;

int main(){

    fscanf(f1,"%d",&a);
    fscanf(f2,"%d",&b);

    if(a != b){
        printf("WA\n");
        while(true);
    }
    printf("OK\n");

    fclose(f1);
    fclose(f2);

    return 0;
}
