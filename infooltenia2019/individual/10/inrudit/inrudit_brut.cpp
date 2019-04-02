#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

FILE *f = fopen("inrudit.in","r");
FILE *g = fopen("inrudit.ok","w");

int k,n;
char c[1005];

int main(){

    fscanf(f,"%d\n",&k);

    fgets(c + 1,1005,f);

    n = strlen(c + 1);
    n -= (c[n] == '\n');

    while(next_permutation(c + 1,c + 1 + n)){
        k--;
        if(k == 0){
            fputs(c + 1,g);
            return 0;
        }
    }

    fprintf(g,"-1");

    return 0;
}
