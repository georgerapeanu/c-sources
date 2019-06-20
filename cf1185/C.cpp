#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int TMAX = 100;

int n,m;
int t[NMAX + 5];

int fr[TMAX + 5];

int main() {

    scanf("%d %d",&n,&m);

    int sum = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d",&t[i]);
        sum += t[i];

        int tmp_sum = sum - m,ans = 0;

        for(int j = TMAX; j > 0; j--) {
            if(tmp_sum <= 0) {
                break;
            }
            if(tmp_sum > fr[j] * j) {
                tmp_sum -= fr[j] * j;
                ans += fr[j];
            }
            else {
                ans += ((tmp_sum + j - 1) / j);
                tmp_sum = 0;
                break;
            }
        }

        printf("%d ",ans);

        fr[t[i]]++;
    }

    return 0;
}
