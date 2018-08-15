#include <cstdio>
using namespace std;
FILE *f = fopen("suma.in","r");
FILE *g = fopen("suma.out","w");
long long N,P;
int main()
{
    fscanf(f,"%lld %lld",&N,&P);
    long long a = N,b = N + 1,c = 2LL * N - 2;
    if(a % 3 == 0){
        a /= 3;
    }
    else if(b % 3 == 0){
        b /= 3;
    }
    else{
        c /= 3;
    }
    if(a % 2 == 0){
        a /= 2;
    }
    else if(b % 2 == 0){
        b /= 2;
    }
    else{
        c /= 2;
    }
    a = a * b % P;
    a = a * c % P;
    fprintf(g,"%lld",a);
    fclose(f);
    fclose(g);
    return 0;
}
