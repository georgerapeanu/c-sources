#include <bits/stdc++.h>
#include <chrono>

using namespace std;

const int NMAX = 20;

int main(){
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    int n = gen() % NMAX + 1;
    int k = gen() % n + 1;
    int vmax = gen() % 20 + 1;

    printf("%d %d\n",n,k);

    for(int i = 1;i <= n;i++){
        printf("%d ",int(gen() % vmax + 1));
    }

    return 0;
}
