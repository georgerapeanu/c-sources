#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("unique.in","r");
FILE *g = fopen("unique.ok","w");

const int TMAX = 10;
const int NMAX = 1e5;

int t;
int n;
int v[NMAX + 5];
int fr[NMAX + 5];

int main() {

    fscanf(f,"%d",&t);

    while(t--) {
        fscanf(f,"%d",&n);

        for(int i = 1; i <= n; i++) {
            fscanf(f,"%d",&v[i]);
        }

        int ans = 0;

        for(int i = 1; i <= n; i++) {
            int ma = 0;
            int mex = 1;
            for(int j = i; j <= n; j++) {
                ma = max(v[j],ma);
                fr[v[j]]++;
                while(fr[mex]) {
                    mex++;
                }
                if(mex > ma) {
                    ans = max(ans,j - i + 1);
                }
            }
            for(int j = i; j <= n; j++) {
                fr[v[j]] = 0;
            }
        }
        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
