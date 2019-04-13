#include <cstdio>

using namespace std;

const int NMAX  = 1e3;

int n,m;
int v[NMAX + 5][NMAX + 5];

int fr[NMAX + 5][NMAX + 5];

int tmp_rows[NMAX + 5],len;

bool ok(int val) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            fr[i][j] = 0;
        }
    }

    for(int j = 1; j <= m; j++) {
        len = 0;
        for(int i = 1; i <= n; i++) {
            if(v[i][j] >= val) {
                tmp_rows[++len] = i;
            }
        }

        for(int i = 1; i <= len; i++) {
            for(int j = 1; j < i; j++) {
                fr[tmp_rows[i]][tmp_rows[j]]++;
                if(fr[tmp_rows[i]][tmp_rows[j]] > 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d",&v[i][j]);
        }
    }

    int st = 0,dr = 1e9 + 1;

    while(dr - st > 1) {

        int mid = (st + dr) / 2;

        if(ok(mid)) {
            st = mid;
        }
        else {
            dr = mid;
        }
    }

    printf("%d\n",st);

    return 0;
}
