#include <bits/stdc++.h>

using namespace std;

int n;
long long b;

int main(){
    
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    n = gen() % 10 + 1;
    b = gen() % 100 + 1;

    printf("%d %lld\n",n,b);

    for(int i = 1;i <= n;i++){
        printf("%d ",int(gen() % 20 + 1));
    }


    return 0;
}
