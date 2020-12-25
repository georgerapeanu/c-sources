#include <bits/stdc++.h>

using namespace std;

FILE *f1 = fopen("out","r");
FILE *f2 = fopen("ok","r");

int main(){

    int a,b;

    while(fscanf(f1,"%d",&a) != EOF &&  fscanf(f2,"%d",&b) != EOF){

        if(a != b){
            printf("WA\n"); 
            while(true);
        }
    }
    printf("OK\n");
    return 0;
}
