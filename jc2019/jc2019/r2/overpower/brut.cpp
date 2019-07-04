#include <cstdio>
#include <map>

using namespace std;

FILE *f = fopen("overpower.in","r");
FILE *g = fopen("overpower.ok","w");

map<long long,long long> memo;
long long get_power(long long a) {
    if(memo.count(a) == 0) {
        long long ans = 1;
        for(long long i = 2; 1LL * i * i <= a; i++) {
            long long e = 0;
            while(a % i == 0) {
                a /= i;
                e++;
            }
            ans = max(ans,e);
        }
        memo[a] = ans;
    }

    return memo[a];
}

int main() {

    int n;
    fscanf(f,"%d",&n);

    for(int i = 1; i <= n; i++) {
        long long a,b;
        fscanf(f,"%lld %lld",&a,&b);

        long long ans = 1;

        for(long long x = a; x <= b; x++) {
            ans = max(ans,get_power(x));
        }

        fprintf(g,"%lld\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
