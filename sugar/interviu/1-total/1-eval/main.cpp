#include <iostream>
#include <cstdio>

using namespace std;

FILE *f1 = fopen("out","r");
FILE *f2 = fopen("ok","r");

char c1[20000];
char c2[20000];

int main(){

    fgets(c1 + 1,20000,f1);
    fgets(c2 + 1,20000,f2);

    for(int i = 1;i <= 20000;i++){
        if(c1[i] != c2[i]){
            cout << "WA\n";
            while(1);
        }
    }

    cout << "OK\n";

    fclose(f1);
    fclose(f2);

    return 0;
}
