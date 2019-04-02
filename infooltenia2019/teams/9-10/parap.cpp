#include <cstdio>

using namespace std;

FILE *f = fopen("parap.in","r");
FILE *g = fopen("parap.out","w");

int n;
int fr[1 << 10];

int main() {

    fscanf(f,"%d",&n);

    for(int i = 1; i <= n; i++) {
        long long val;
        fscanf(f,"%lld",&val);
        int mask = 0;
        while(val) {
            int cf = val % 10;
            val /= 10;
            mask ^= (1 << cf);
        }
        fr[mask]++;
    }

    long long ans = 0;

    for(int x:fr) {
        ans += 1LL * x * (x - 1) / 2;
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
