#include <cstdio>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

FILE *g = fopen("reg.in","w");

const int TMAX = 10;
const int NMAX = 2e6;
const int VMAX = 5e5;

bool is_comp[VMAX + 5];

int main(){

    vector<int> primes;
    
    for(int i = 2;i <= VMAX;i++){
        if(is_comp[i] == true){
            continue;
        }

        primes.push_back(i);

        for(int j = 2 * i;j <= VMAX;j += i){
            is_comp[j] = true;
        }
    }


    random_device rd;
    mt19937 gen(rd());

    int t = gen() % TMAX + 1;

    fprintf(g,"%d\n",t);

    while(t--){
        int a = gen() % VMAX + 1;
        int b = gen() % VMAX + 1;
        int c = primes[gen() % int(primes.size())];
        int n = gen() % VMAX + 1;
        int k = gen() % VMAX + 1;

        fprintf(g,"%d %d %d %d %d\n",a,b,c,n,k);
    }
    
    fclose(g);
    return 0;
}


