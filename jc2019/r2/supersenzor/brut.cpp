#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("supersenzor.in","r");
FILE *g = fopen("supersenzor.ok","w");

const int NMAX = 50;

int n,t;
int a[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&t);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&a[i]);
    }

    sort(a + 1,a + 1 + n);

    long long bst = 1LL << 60;

    for(int x = t; x <= a[n]; x++) {
        long long cost = 0;
        for(int i = 1; i <= n; i++) {
            cost += ((a[i] + x - 1) / x) * x;
        }
        bst = min(bst,cost);
    }

    fprintf(g,"%lld\n",bst);

    fclose(f);
    fclose(g);

    return 0;
}
