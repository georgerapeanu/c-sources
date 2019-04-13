#include <cstdio>

using namespace std;

FILE *f = fopen("entanglement.in","r");
FILE *g = fopen("entanglement.out","w");

const int NMAX = 300;
const int MOD = 1e9 + 7;

int t,n,m,k;

int v[NMAX + 5][NMAX + 5];

bool found = false;

int a[NMAX + 5];
int b[NMAX + 5][NMAX + 5];

int fr[NMAX * NMAX + 5];

int vals[NMAX + 5][NMAX + 5];
int lens[NMAX + 5];

int solve(int i) {

    if(i > n) {
        found = true;
        int ans = 1;
        for(int j = 1; j <= m; j++) {
            if(b[i - 1][j] == 0) {
                ans = 1LL * ans * k % MOD;
            }
        }
        return ans;
    }

    int ans = 0;

    for(int j = 1; j <= m; j++) {
        if(b[i - 1][j] != v[i][j] && fr[v[i][j]] == 0) {
            vals[i][++lens[i]] = v[i][j];
            fr[v[i][j]]++;
        }
    }

    for(int j = 1; j <= lens[i]; j++) {
        fr[vals[i][j]] = 0;
    }

    int libere = k - lens[i];

    ///libere

    bool ok = true;

    for(int j = 1; j <= m; j++) {
        if(b[i - 1][j] != 0 && b[i - 1][j] != v[i][j]) {
            ok = false;
            break;
        }
    }

    if(ok) {
        for(int j = 1; j <= m; j++) {
            b[i][j] = v[i][j];
        }
        ans = (ans + 1LL * solve(i + 1) * libere) % MOD;
    }

    for(int k = 1; k <= lens[i]; k++) {
        a[i] = vals[i][k];

        bool ok = true;

        for(int j = 1; j <= m; j++) {
            if(v[i][j] != a[i] && b[i - 1][j] != 0 && b[i - 1][j] != v[i][j]) {
                ok = false;
                break;
            }
        }

        if(ok) {
            for(int j = 1; j <= m; j++) {
                if(v[i][j] != a[i]) {
                    b[i][j] = v[i][j];
                }
                else {
                    b[i][j] = b[i - 1][j];
                }
            }

            ans = (ans + solve(i + 1)) % MOD;
        }
    }

    lens[i] = 0;

    return ans;
}

int main() {

    fscanf(f,"%d %d %d %d",&t,&n,&m,&k);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fscanf(f,"%d",&v[i][j]);

            if(v[i][j] > k) {
                fprintf(g,"%s",(t == 1 ? "NU":"0"));
                return 0;
            }
        }
    }

    int ans = solve(1);

    if(t == 1) {
        fputs((found == true ? "DA":"NU"),g);
    }
    else {
        fprintf(g,"%d\n",ans);
    }

    return 0;
}
