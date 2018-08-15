#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("ejoc.in","r");
FILE *g=fopen("ejoc.out","w");
int T;
long long A,B;
long long gcd(long long A,long long B)
{
    if(!B) return A;
    return gcd(B,A%B);
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%lld %lld",&A,&B);
        long long nr=max(A,B)/gcd(A,B);
        fprintf(g,"%s\n",(nr%2 ? "Dalila":"Denisa"));
    }
    fclose(f);
    fclose(g);
    return 0;
}
