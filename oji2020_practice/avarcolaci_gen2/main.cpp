#include <cstdio>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

FILE *g = fopen("avarcolaci.in","w");

const int NMAX = 1e5;
const int VMAX = 1e6;
const int TMAX = 15;

int t;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    t = gen() % TMAX + 1;

    fprintf(g,"%d\n",t);

    while(t--){
        int n = gen() % NMAX + 1;
        int vmax = gen() % VMAX + 1;
        int forced_maj = (gen() % 100 <= 50);
        int forced_number = gen() % vmax + 1;

        vector<int> tmp;

        if(forced_maj){
            tmp = vector<int>(n,forced_number);
        }

        while((int)tmp.size() < 2 * n){
            tmp.push_back(gen() % vmax + 1);
        }

        fprintf(g,"%d\n",n);
        for(auto it:tmp){
            fprintf(g,"%d ",it);
        }
        fprintf(g,"\n");
    }

    fclose(g);

    return 0;
}
