#include <bits/stdc++.h>

using namespace std;

const int MASK = (1 << 4) - 1;

const int NMAX = 10;
const int QMAX = 10;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    
    int n = gen() % NMAX + 1;
    int q = gen() % QMAX + 1;

    printf("%d %d\n",n,q);

    for(int i = 1;i <= n;i++){
        printf("%d ",(gen() & MASK));
    }
    printf("\n");
    for(int i = 1;i <= q;i++){
        int t = ((gen()) % 100 > 30) + 1;
        int l = gen() % n + 1;
        int r = gen() % n + 1;
        int x = (gen() & MASK);

        if(l > r){
            swap(l,r);
        }

        printf("%d %d %d %d\n",t,l,r,x);
    }

    return 0;
}
