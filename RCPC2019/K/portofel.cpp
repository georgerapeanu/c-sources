#include <cstdio>

using namespace std;

FILE *f = fopen("portofel.in","r");
FILE *g = fopen("portofel.out","w");

const int NMAX = 1e5;

int t,n,m;
int a[NMAX + 5];
int b[NMAX + 5];

int main() {

    fscanf(f,"%d",&t);

    while(t--) {
        fscanf(f,"%d %d",&n,&m);

        for(int i = 1; i <= n; i++) {
            fscanf(f,"%d",&a[i]);
        }

        a[0] = -1;
        a[n + 1] = 1e9 + 3;

        for(int i = 1; i <= m; i++) {
            fscanf(f,"%d",&b[i]);
        }

        int lst = 1;
        int ans = 0;

        for(int i = 0; i <= n; i++) {
            if(a[i + 1] <= b[lst]) {
                continue;
            }

            if(lst <= m) {
                ans++;
            }

            while(lst <= m && b[lst] <= a[i + 1]) {
                lst++;
            }
        }

        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
