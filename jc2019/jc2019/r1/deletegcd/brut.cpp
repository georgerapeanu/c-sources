#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

FILE *f = fopen("deletegcd.in","r");
FILE *g = fopen("deletegcd.ok","w");

const int NMAX = 1e6;
const int QMAX = 1e6;
const int VMAX = 1e6;

int gcd(int a,int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

int n,q;
int v[NMAX + 5];
int pref[NMAX + 5];
int suff[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    while(q--) {
        int l,r;
        fscanf(f,"%d %d",&l,&r);
        pref[l] = v[l];
        for(int i = l + 1; i <= r; i++) {
            pref[i] = gcd(pref[i - 1],v[i]);
        }
        suff[r] = v[r];
        for(int i = r - 1; i >= l; i--) {
            suff[i] = gcd(suff[i + 1],v[i]);
        }

        int ans = max(pref[r - 1],suff[l + 1]);

        for(int i = l + 1; i < r && ans == 1; i++) {
            ans = max(ans,gcd(pref[i - 1],suff[i + 1]));
        }

        fputc('0' + (ans > 1),g);
    }

    return 0;
}
