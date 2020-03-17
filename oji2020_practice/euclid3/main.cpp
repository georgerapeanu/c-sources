#include <cstdio>

using namespace std;

FILE * f = fopen("euclid3.in","r");
FILE * g = fopen("euclid3.out","w");

long long ext_gcd(long long a,long long b,long long &x,long long &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }

    long long d = ext_gcd(b,a % b,x,y);
    long long x0 = y;
    long long y0 = x - (a / b) * y;
    x = x0;
    y = y0;
    return d;
}

int t;

int main(){

    fscanf(f,"%d",&t);

    while(t--){
        long long a,b,c;
        fscanf(f,"%lld %lld %lld",&a,&b,&c);
        long long x,y;
        long long d = ext_gcd(a,b,x,y);
        if(c % d != 0){
            fprintf(g,"0 0\n");
        }
        else{
            fprintf(g,"%lld %lld\n",x * (c / d),y * (c / d));
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
