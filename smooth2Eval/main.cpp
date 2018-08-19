#include <cstdio>
using namespace std;
FILE * f1 = fopen("smooth2.out","r");
FILE * f2 = fopen("smooth2.ok","r");
int main()
{
    int a,b;
    fscanf(f1,"%d",&a);
    fscanf(f2,"%d",&b);
    if(a == b){
        printf("OK!\n");
    }
    else{
        printf("WA!\n");
        while(1){
            ;
        }
    }
    return 0;
}
