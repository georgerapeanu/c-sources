#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("task2.in","r");
FILE *g = fopen("task2.ok","w");

const int NMAX = 1e6;
const int VMAX = 1e4;

int n,q;
long long v[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%lld",&v[i]);
    }

    while(q--) {
        int t,l,r;

        fscanf(f,"%d %d %d",&t,&l,&r);

        if(t == 1) {
            int x;
            fscanf(f,"%d",&x);

            for(int i = l; i <= r; i++) {
                v[i] = max(v[i],1LL * x);
            }
        }

        else if(t == 2) {
            int x;
            fscanf(f,"%d",&x);

            for(int i = l; i <= r; i++) {
                v[i] = min(v[i],1LL * x);
            }
        }

        else if(t == 3) {
            int x;
            fscanf(f,"%d",&x);

            for(int i = l; i <= r; i++) {
                v[i] += x;
            }
        }

        else {
            long long ans = 0;

            for(int i = l; i <= r; i++) {
                ans += v[i];
            }

            fprintf(g,"%lld\n",ans);
        }
    }

    fclose(f);
    fclose(g);
    return 0;
}
