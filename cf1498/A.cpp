#include <bits/stdc++.h>

using namespace std;

int t;
long long n;

long long digitsum(long long n){
    long long sum = 0;

    while(n){
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

long long gcd(long long a,long long b){
    if(!b){
        return a;
    }
    return gcd(b,a % b);
}

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%lld",&n);

        while(gcd(n,digitsum(n)) == 1){
            n++;
        }
        printf("%lld\n",n);
    }

    return 0;
}
