#include <bits/stdc++.h>

using namespace std;

int t;
int a,b,c;

int main() {

    scanf("%d",&t);

    while(t--){
        scanf("%d %d %d",&a,&b,&c);
        printf("%lld\n",((long long)a) + b + c - 1);
    }

    return 0;
}
