#include <cstdio>

using namespace std;

long long a,b;

int main(){


    scanf("%lld %lld",&a,&b);

    if(a <= 2004 && b <= 2004){
        printf("-1\n");
    }
    else{
        printf("%lld\n",a + b);
    }

    return 0;
}
