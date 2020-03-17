#include <cstdio>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

FILE *g = fopen("lexicografic.in","w");

const int NMAX = 100;
const int VMAX = NMAX;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int t = 20;

    fprintf(g,"%d\n",t);

    while(t--){
        int vmax = gen() % VMAX + 1;
        int n = gen() % NMAX + 2;
        int k = gen() % (n * (n - 1) / 2) + 1;
        fprintf(g,"%d %d\n",n,k);
        for(int i = 1;i <= n;i++){
            fprintf(g,"%d ",int(gen() % vmax + 1));
        }
        fprintf(g,"\n");
    }

    return 0;
}
