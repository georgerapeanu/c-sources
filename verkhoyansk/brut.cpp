#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("verkhoyansk.in","r");
FILE *g = fopen("verkhoyansk.ok","w");

const int NMAX = 3e5;
const int QMAX = 6e5;

int n,q;
bool has[NMAX + 5];
int v[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    for(int i = 1; i <= q; i++) {
        int l,r;
        fscanf(f,"%d %d",&l,&r);
        memset(has,0,sizeof(has));

        for(int i = l + 1; i <= r + 1; i++) {
            has[v[i]] = true;
        }

        int ans = 1;
        while(has[ans]) {
            ans++;
        }

        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
