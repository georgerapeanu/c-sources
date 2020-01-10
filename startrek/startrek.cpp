#include <cstdio>
#include <vector>

using namespace std;

FILE *f = fopen("startrek.in","r");
FILE *g = fopen("startrek.out","w");

const int NMAX = 1e5;

int n,p,q,m;

int st[NMAX + 5];
int dr[NMAX + 5];
int hi[NMAX + 5];
int lo[NMAX + 5];
int suff_min[NMAX + 5];
int sol[NMAX + 5];

int main() {

    fscanf(f,"%d %d %d %d",&n,&p,&q,&m);

    for(int i = 1; i <= n; i++) {
        st[i] = 2e9;
    }

    while(m--) {
        int pos,val;
        fscanf(f,"%d %d",&pos,&val);
        st[val] = min(pos,st[val]);
        dr[val] = max(pos,dr[val]);
    }

    suff_min[n + 1] = 2 * NMAX;

    for(int i = n; i; i--) {
        suff_min[i] = min(suff_min[i + 1],st[i]);
    }

    for(int year = 1; year <= n; year++) {
        lo[year] = max(lo[year - 1] + p,dr[year]);
        hi[year] = min(min(hi[year - 1] + q,st[year] + q - 1),suff_min[year + 1] - 1);
    }

    int ans = 0;

    for(int year = 1; year <= n; year++) {
        if(lo[year] <= n && hi[year] >= n) {
            ans = year;
        }
    }

    fprintf(g,"%d\n",ans);

    int pos = n;

    while(pos) {
        int ant = min(hi[ans - 1],pos - p);

        while(pos > ant) {
            sol[pos--] = ans;
        }
        ans--;
    }

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",sol[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
