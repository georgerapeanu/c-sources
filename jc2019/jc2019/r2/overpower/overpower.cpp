#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("overpower.in","r");
FILE *g = fopen("overpower.out","w");

const int BUCK = 4e4;

int n;

int primes[BUCK + 1];
bool is_comp[BUCK + 1];
int len;

long long my_sqrt(long long val) {
    long long l = 0,r = 1e9 + 1;

    while(r - l > 1) {
        long long mid = (l + r) / 2;
        if(mid * mid <= val) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return l;
}

long long my_cbrt(long long val) {
    long long l = 0,r = 1e6 + 1;

    while(r - l > 1) {
        long long mid = (l + r) / 2;

        if(mid * mid * mid <= val) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return l;
}

int main() {

    for(int i = 2; i <= BUCK; i++) {
        if(is_comp[i] == false) {
            primes[++len] = i;
            for(int j = 2 * i; j <= BUCK; j += i) {
                is_comp[j] = true;
            }
        }
    }

    fscanf(f,"%d",&n);

    while(n--) {
        long long a,b;
        fscanf(f,"%lld %lld\n",&a,&b);

        int ans = 1;
        for(int i = 1; i <= len; i++) {
            long long x = primes[i];
            int e = 1;

            while(true) {
                if((b / x) - ((a - 1) / x) > 0) {
                    ans = max(ans,e);
                }
                else {
                    break;
                }
                if(x > b / primes[i]) {
                    break;
                }
                x = x * primes[i];
                e++;
            }
        }

        if(my_sqrt(b) - my_sqrt(a - 1) > 0) {
            ans = max(ans,2);
        }

        if(my_cbrt(b) - my_cbrt(a - 1) > 0) {
            ans = max(ans,3);
        }

        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
