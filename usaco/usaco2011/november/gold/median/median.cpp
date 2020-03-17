#include <cstdio>

using namespace std;

FILE *f = fopen("median.in","r");
FILE *g = fopen("median.out","w");

const int NMAX = 1e5;

int n,x;
int v[NMAX + 5];

int aib[2 * NMAX + 5];

void update(int pos,int val) {
    pos += NMAX + 1;

    for(; pos <= 2* NMAX + 5; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int query(int pos) {
    pos += NMAX + 1;

    int ans = 0;
    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }

    return ans;
}

int main() {

    fscanf(f,"%d %d",&n,&x);

    long long ans = 0;

    update(0,1);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
        v[i] = (v[i] >= x ? 1:-1);
        v[i] += v[i - 1];
        ans += query(v[i]);
        update(v[i],1);
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
