#include <cstdio>
#include <algorithm>
using namespace std;
long long N;
int Q;
long long x;
long long solve(long long N,long long x){
    if(N == 1){
        return 1;
    }
    if(N & 1){
        if(x & 1){
            return (x + 1) / 2;
        }
        return N / 2 + 1 + solve(N / 2,(x / 2 - 1 == 0 ? N / 2:x / 2 - 1));
    }
    else{
        if(x & 1){
            return (x + 1) / 2;
        }
        return N / 2 + solve(N / 2,x / 2);
    }
}
int main()
{
    scanf("%I64d",&N);
    scanf("%d",&Q);
    while(Q--){
        scanf("%I64d",&x);
        printf("%I64d\n",solve(N,x));
    }
    return 0;
}
