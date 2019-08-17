#include <cstdio>
#include <random>
#include <algorithm>

using namespace std;

FILE *g = fopen("hacker.in","w");

const int NMAX = 10;
const int KMAX = 10;
const int WN = 40;
const int WU = 60;

int main(){

    random_device rd;
    mt19937 gen(rd());

    int n,k;

    n = gen() % NMAX + 1;
    k = gen() % KMAX + 1;

    fprintf(g,"%d %d\n",n,k);

    for(int i = 1;i <= n;i++){
        int val = gen() % (WN + WU);
        if(val < WN){
            fprintf(g,"%d",int(gen() % k));
        }
        else{
            fprintf(g,"?");
        }
    }

    fclose(g);

    return 0;
}
