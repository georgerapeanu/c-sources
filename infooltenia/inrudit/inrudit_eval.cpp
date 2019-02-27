#include<cstdio>

using namespace std;

FILE *f1 = fopen("inrudit.out","r");
FILE *f2 = fopen("inrudit.ok","r");

char c1[1005];
char c2[1005];

int main(){

    fgets(c1 + 1,1005,f1);
    fgets(c2 + 1,1005,f2);
    
    for(int i = 1;i < 1005;i++){
        if(c1[i] != c2[i]){
            printf("WA\n");

            while(1);
        }
    }

    printf("OK\n");

    return 0;
}
