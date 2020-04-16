#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("covrigi.in","r");
FILE *g = fopen("covrigi.out","w");

const int NMAX = 50000;

int n,m,k;
int v[NMAX + 5];
int c[NMAX + 5];

int main() {

    fscanf(f,"%d %d %d",&n,&m,&k);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    for(int i = 1; i <= m; i++) {
        fscanf(f,"%d",&c[i]);
    }

    sort(c + 1,c + 1 + m);
    reverse(c + 1,c + 1 + m);

    int place = 1;

    for(int i = 1; i <= m; i++) {
        place += c[i];
    }

    long long ans = -1e18;

    for(int i = 0; i <= m; i++) {
        place -= c[i];
        ans = max(ans,v[place] - 1LL * k * i);
    }

    fprintf(g,"%lld\n",ans);

    return 0;
}
