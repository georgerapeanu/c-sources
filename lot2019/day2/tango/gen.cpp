#include <bits/stdc++.h>

using namespace std;

int main() {

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int n = 1e6;
    int t = 1e6;

    for(int i = 1; i <= n; i++) {
        printf("%c",(gen() % 2 == 1 ? 'B':'F'));
    }
    printf("\n");

    printf("%d\n",t);

    for(int i = 1; i <= t; i++) {
        int l = gen() % n + 1;
        int r = gen() % n + 1;
        if(r < l) {
            swap(l,r);
        }
        printf("%d %d\n",l,r);
    }

    return 0;
}
