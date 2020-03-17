#include <cstdio>

using namespace std;

FILE *f = fopen("avarcolaci.in","r");
FILE *f1 = fopen("avarcolaci.out","r");
FILE *f2 = fopen("avarcolaci.ok","r");

char a[100];
char b[100];

int main(){
    int t;
    fscanf(f,"%d",&t);

    while(t--){
        fgets(a + 1,100,f1);
        fgets(b + 1,100,f2);
        for(int i = 1;;i++){
            if((a[i] == '\n' || a[i] == '\0') && (b[i] == '\n' || b[i] == '\0')){
                break;
            }
            if(a[i] != b[i]){
                printf("WA\n");
                while(true);
            }
        }
    }
    printf("OK\n");

    return 0;
}
