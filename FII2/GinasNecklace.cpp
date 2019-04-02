#include <iostream>
#include <algorithm>

using namespace std;

int v[int(6e3) + 4];

int d[int(6e3) + 4];
int sum[int(6e3) + 4];
int st,dr;

int main() {

    int n,m;

    cin >> n >> m;

    int mdist = 0;

    for(int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        v[a] = 1;
        v[a + m] = 1;
    }

    int st = 0;
    int ans = 1 << 30;

    st = 1;

    for(int i = 1; i <= 2 * m; i++) {
        if(v[i] == 1) {
            d[++dr] = i;
            sum[dr] = sum[dr - 1] + i;
            if(dr - st + 1 >= n) {
                if(dr - st + 1 > n) {
                    st++;
                }
                int ind = (st + dr) / 2;
                int cost = d[ind] * (ind - st + 1) - (sum[ind] - sum[st - 1]) +
                           (sum[dr] - sum[ind]) - d[ind] * (dr - ind) -
                           (ind - st) * (ind - st + 1) / 2 -
                           (dr - ind) * (dr - ind + 1) / 2;


                ans = min(ans,cost);
            }
        }

    }

    cout << ans;

    return 0;
}
