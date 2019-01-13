#define JUDGE
#include <cstdio>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("sir42.in","r");
FILE *g = fopen("sir42.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 250;

int n,k;
int v[NMAX + 5];

char c[NMAX + 5];

int main() {

    fscanf(f,"%d %d\n",&n,&k);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d ",&v[i]);
        v[i] += (v[i] >= 0);
    }

    if(v[1] == -1) {
        for(int i = 1; i <= n; i++) {
            c[i] = '0';
        }
        fputs(c + 1,g);
        return 0;
    }

    int fst_neg = -1;
    int r1 = (v[1] == -1 ? n : v[1]);

    for(int i = 1; i <= n; i++) {
        if(v[i] != -1) {
            if(i < n && v[i] != v[i + 1]) {
                c[i] = '1';
            }
            else {
                c[i] = '0';
            }
        }
        if(v[i] == -1 && fst_neg == -1) {
            fst_neg = i;
        }

        if(v[i] != -1) {
            c[v[i]] = '1';
        }
        if(v[i + 1] != -1) {
            c[v[i + 1]] = '1';
            for(int j = v[i] + 1; j < v[i + 1]; j++) {
                c[j] = '0';
            }
        }
        else if(v[i] != -1) {
            for(int j = v[i] + 1; j <= n; j++) {
                c[j] = '0';
            }
        }
    }

    ///unknown area [fst_-1,R[1] - 1]

    if(fst_neg != -1 && fst_neg <= r1 - 1) {
        int cnt = k;
        for(int j = 1; j <= r1; j++) {
            cnt -= (c[j] == '1');
        }

        for(int k = fst_neg; k < r1; k++) {
            c[k] = '0' + (cnt > 0);
            cnt--;
        }
    }

    fputs(c + 1,g);

    return 0;
}
