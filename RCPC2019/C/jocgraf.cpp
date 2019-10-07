#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("jocgraf.in","r");
FILE *g = fopen("jocgraf.out","w");

const int NMAX = 1e5;

int t;
int n,m;
int a[NMAX + 5];

int main() {

    fscanf(f,"%d",&t);

    while(t--) {
        fscanf(f,"%d %d",&n,&m);
        for(int i = 1; i <= n; i++) {
            fscanf(f,"%d",&a[i]);
            a[i] *= 2;
        }
        for(int i = 1; i <= m; i++) {
            int x,y,z;
            fscanf(f,"%d %d %d",&x,&y,&z);
            a[x] += z;
            a[y] += z;
        }
        sort(a + 1,a + 1 + n);
        reverse(a + 1,a + 1 + n);
        long long ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += ((i & 1) ? 1:-1) * a[i];
        }
        fprintf(g,"%lld\n",ans / 2);
    }


    fclose(f);
    fclose(g);

    return 0;
}
