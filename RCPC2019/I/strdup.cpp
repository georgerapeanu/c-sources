#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("strdup.in","r");
FILE *g = fopen("strdup.out","w");

const int NMAX = 1e3;

int t;
int n;
char c[NMAX + 5];
int lcs[NMAX + 5];
int ma[NMAX + 5];

int gcd(int a,int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

int main() {

    fscanf(f,"%d\n",&t);

    while(t--) {
        fgets(c + 1,NMAX + 5,f);
        n = strlen(c + 1);
        n -= (c[n] == '\n' || c[n] == '\0');
        n -= (c[n] == '\n' || c[n] == '\0');
        for(int i = 1; i <= n; i++) {
            ma[i] = 0;
            for(int j = i - 1; j; j--) {
                lcs[j] = (c[i] == c[j] ? lcs[j - 1] + 1:0);
                ma[j] = max(ma[j],lcs[j]);
                ma[i] = max(ma[i],lcs[j]);
            }
        }

        int cnt = 0;

        for(int i = 1; i <= n; i++) {
            cnt += ma[i];
        }

        int a = gcd(cnt,n * (n + 1) / 2);
        fprintf(g,"%d/%d\n",cnt / a,(n * (n + 1) / 2) / a);
    }

    fclose(f);
    fclose(g);

    return 0;
}
