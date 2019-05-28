#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

using namespace std;

const int NMAX = 3e5;

int n,m;
int v[NMAX + 5];
int tmp_v[NMAX + 5];

bool ok(int val) {
    for(int i = 1; i <= n; i++) {
        tmp_v[i] = v[i];
        if(tmp_v[i - 1] > tmp_v[i]) {
            if(tmp_v[i] + val < tmp_v[i - 1]) {
                return false;
            }
            tmp_v[i] = tmp_v[i - 1];
        }
        else {
            if(val >= m - tmp_v[i] && (tmp_v[i] + val) % m >= tmp_v[i - 1] && (tmp_v[i] + val) % m <= tmp_v[i]) {
                tmp_v[i] = tmp_v[i - 1];
            }
        }
    }
    return true;
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    int st = -1;
    int dr = m;

    while(dr - st > 1) {
        int mid = (st + dr) / 2;

        if(ok(mid)) {
            dr = mid;
        }
        else {
            st = mid;
        }
    }

    printf("%d",dr);

    return 0;
}
