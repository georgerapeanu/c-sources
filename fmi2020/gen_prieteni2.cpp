#include <cstdio>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

const int NMAX = 10;
const int QMAX = 100;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int n = gen() % NMAX + 2;
    int q = gen() % QMAX + 1;

    printf("%d %d\n",n,q);

    for(int i = 1;i <= q;i++){
        int t = gen() % 3 + 1;
        if(t <= 2){
            int x = gen() % (n - 1) + 1;
            printf("%d %d\n",t,x);
        }
        else{
            int l = gen() % n + 1;
            int r = gen() % n + 1;
            if(r < l){
                swap(l,r);
            }
            printf("%d %d %d\n",t,l,r);
        }
    }

    return 0;
}

