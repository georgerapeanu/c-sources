#include <cstdio>
using namespace std;
FILE * f1 = fopen("zoro.out","r");
FILE * f2 = fopen("zoro.ok","r");
int main()
{
    int a,b;
    fscanf(f1,"%d",&a);
    fscanf(f2,"%d",&b);
    if(a == b){
        printf("OK!\n");
    }
    else if(a < 0 && b < 0){
        printf("Wrong Test\n");
    }
    else{
        printf("WA!\n");
        while(1){
            ;
        }
    }
    return 0;
}
