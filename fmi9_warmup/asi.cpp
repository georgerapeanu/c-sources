#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("asi.in","r");
FILE *g = fopen("asi.out","w");

const int VMAX = 1e6;
const long long REAL_VMAX = 1e12;


bool not_prime[VMAX + 5];
vector<long long> stuff;

int main() {

    not_prime[0] = not_prime[1] = true;

    for(int i = 2; i <= VMAX; i++) {
        if(not_prime[i] == true) {
            continue;
        }
        for(int j = i * 2; j <= VMAX; j += i) {
            not_prime[j] = true;
        }
        for(long long j = 1LL * i * i; j <= REAL_VMAX; j *= i) {
            stuff.push_back(j);
        }
    }

    sort(stuff.begin(),stuff.end());

    int q;

    fscanf(f,"%d",&q);

    while(q--) {
        long long a,b;
        fscanf(f,"%lld %lld",&a,&b);
        fprintf(g,"%d\n",int(lower_bound(stuff.begin(),stuff.end(),b + 1) - lower_bound(stuff.begin(),stuff.end(),a)));
    }

    fclose(f);
    fclose(g);

    return 0;
}
