#include <cstdio>

using namespace std;

FILE *f1 = fopen("permpower.out","r");
FILE *f2 = fopen("permpower.ok","r");

int main(){
    
    int x,y;
    fscanf(f1,"%d",&x);
    fscanf(f2,"%d",&y);

    if(x != y){
        printf("WA\n");
        while(true);
    }

    printf("OK\n");

    return 0;
}
