#include <cstdio>

using namespace std;

FILE *f = fopen("calafat.in","r");
FILE *g = fopen("calafat.ok","w");

const int NMAX = 2e5;

int n,q;
int v[NMAX + 5];
int fst[NMAX + 5];
int lst[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    while(q--) {
        int l,r;

        fscanf(f,"%d %d",&l,&r);

        long long ans = 0;

        for(int i = l; i <= r; i++) {
            if(fst[v[i]] == 0) {
                fst[v[i]] = i;
            }
            lst[v[i]] = i;
        }

        for(int i = l; i <= r; i++) {
            if(fst[v[i]] == i) {
                ans += lst[v[i]] - fst[v[i]];
            }
            fst[v[i]] = lst[v[i]] = 0;
        }

        fprintf(g,"%lld\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
