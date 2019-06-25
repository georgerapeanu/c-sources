#include <cstdio>

using namespace std;

FILE *f1 = fopen("reg.out","r");
FILE *f2 = fopen("reg.ok","r");

int main(){
    int a,b;

    while(fscanf(f1,"%d",&a) == 1 && fscanf(f2,"%d",&b) == 1){
        if(a != b){
            printf("WA %d %d\n",a,b);
            while(true);
        }
    }

    printf("OK\n");
    fclose(f1);
    fclose(f2);
    return 0;
}
