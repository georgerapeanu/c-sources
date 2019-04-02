#include <cstdio>

using namespace std;

FILE *f = fopen("nrecou.in","r");
FILE *g = fopen("nrecou.out","w");

const int NMAX = 1e6;
const int MOD = 1e9 + 17;

int n;
int ans[NMAX + 5];
int sgn[NMAX + 5];
bool not_prime[NMAX + 5];
int primes[NMAX + 5],len;

int main() {

    for(int i = 2; i <= NMAX; i++) {
        if(not_prime[i] == false) {
            primes[++len] = i;
            sgn[i] = -1;
        }

        for(int j = 1; j <= len && primes[j] <= NMAX / i; j++) {
            if(i % primes[j] == 0) {
                not_prime[primes[j] * i] = true;
                sgn[primes[j] * i] = 0;
                break;
            }
            else {
                not_prime[primes[j] * i] = true;
                sgn[primes[j] * i] = -sgn[i];
            }
        }
    }

    ans[0] = 9;
    for(int i = 1; i <= NMAX; i++) {
        ans[i] = 10LL * ans[i - 1] % MOD;
    }

    fscanf(f,"%d",&n);

    int rans = 0;

    for(int i = 2; i <= n; i++) {
        if(n % i == 0) {
            if(sgn[i] == -1) {
                rans += ans[n / i - 1];
                if(rans >= MOD) {
                    rans -= MOD;
                }
            }
            else if(sgn[i] == 1) {
                rans -= ans[n / i - 1];
                if(rans < 0) {
                    rans += MOD;
                }
            }
        }
    }

    fprintf(g,"%lld",rans);

    fclose(f);
    fclose(g);

    return 0;
}
