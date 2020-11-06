#include <cstdio>

using namespace std;

int main(){

    FILE *f,*g;

    f = fopen("out","r");
    g = fopen("ok","r");

    int a,b;
    fscanf(f,"%d",&a);
    fscanf(g,"%d",&b);

    if(a != b){
        printf("WA\n");
        while(true);
    }

    printf("ACC\n");

    return 0;
}
