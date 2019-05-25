#include <cstdio>

using namespace std;

long long x;
long long r;
long long d;

int main(){
    
    scanf("%lld %lld %lld",&r,&d,&x);

    for(int i = 1;i <= 10;i++){
        x = r * x - d;

        printf("%lld\n",x);
    }

    return 0;
}
