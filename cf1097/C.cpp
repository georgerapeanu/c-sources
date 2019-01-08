#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
int total[NMAX + 5];
int low[NMAX + 5];
char c[5 * NMAX + 5];
int suply[5 * NMAX + 5];
int demand[5 * NMAX + 5];

int main() {
    scanf("%d\n",&n);

    for(int i = 1; i <= n; i++) {
        fgets(c + 1,5 * NMAX + 5,stdin);
        for(int j = 1; c[j] == '(' || c[j] == ')'; j++) {
            total[i] += (c[j] == '(' ? 1:-1);
            low[i] = min(low[i],total[i]);
        }

        if(total[i] > 0 && low[i] < 0) {
            continue;
        }
        if(total[i] == 0 && low[i] != 0) {
            continue;
        }
        if(total[i] < 0 && low[i] < total[i]) {
            continue;
        }
        if(total[i] >= 0) {
            suply[total[i]]++;
        }
        if(total[i] <= 0) {
            demand[-total[i]]++;
        }
    }

    int ans = 0;

    for(int i = 1; i <= 5e5 + 2; i++) {
        ans += min(suply[i],demand[i]);
    }

    ans += suply[0] / 2;

    printf("%d",ans);

    return 0;
}
