#include <bits/stdc++.h>
#include <chrono>

using namespace std;

const int NMAX = 100;

int main(){
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    int n = gen() % NMAX + 1;
    int k = gen() % n + 1;
    int vmax = gen() % 21 - 10;

    printf("%d\n",n);

    for(int i = 1;i <= n;i++){
        printf("%d ",int(gen() % vmax + 1));
    }

    int q = gen() % NMAX + 1;

    for(int i = 1;i <= q;i++){
        int l = gen() % n + 1;
        int r = gen() % n + 1;
        if(r < l){
            swap(l,r);
        }
        printf("%d %d\n",l,r);
    }

    return 0;
}
