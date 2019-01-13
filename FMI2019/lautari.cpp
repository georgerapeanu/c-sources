#define JUDGE
#include <cstdio>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("lautari.in","r");
FILE *g = fopen("lautari.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 1e5;
const int VMAX = 1e5;

int n;
int p,q;
int fr1[VMAX + 5],numdif1,ind1;
int fr2[VMAX + 5],numdif2,ind2;
int v[NMAX + 5];

int main() {

    fscanf(f,"%d %d %d",&n,&p,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    ind1 = ind2 = 1;

    long long ans = 0;

    for(int i = 1; i <= n; i++) {
        numdif1 += (fr1[v[i]] == 0);
        fr1[v[i]]++;
        numdif2 += (fr2[v[i]] == 0);
        fr2[v[i]]++;

        while(numdif1 >= p && ind1 <= i && numdif1 - (fr1[v[ind1]] == 1) >= p) {
            numdif1 -= (fr1[v[ind1]] == 1);
            fr1[v[ind1]]--;
            ind1++;
        }

        while(numdif2 > q && ind2 <= i) {
            numdif2 -= (fr2[v[ind2]] == 1);
            fr2[v[ind2]]--;
            ind2++;
        }

        if(numdif1 >= p && numdif2 <= q) {
            ans += ind1 - ind2 + 1;
        }
    }

    fprintf(g,"%lld",ans);


    return 0;
}
