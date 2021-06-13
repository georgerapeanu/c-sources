#include <bits/stdc++.h>

using namespace std;

int main(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int n = rng() % 10 + 1;


    printf("%d\n",n);
    for(int i = 1;i <= n;i++){
        printf("%d ",int(rng() % n));
    }

    return 0;
}
