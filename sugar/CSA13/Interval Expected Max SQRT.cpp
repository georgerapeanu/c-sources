#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 1e5;
const int BUCK = 413;

int n,q;
int v[NMAX + 5];
pair<int,int> values[NMAX + 5];
long long ans[QMAX + 5];
pair<int,int> queries[QMAX + 5];
long long dp[BUCK + 5][BUCK + 5];
int cnt1[NMAX + 5];
long long sum1[NMAX + 5];
pair<int,pair<int,int> > nv[BUCK + 5];
int nxt[NMAX + 5];
int ant[NMAX + 5];

int main() {

    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        values[i] = {v[i],i};
    }

    for(int i = 1; i <= q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    sort(values + 1,values + 1 + n);

    for(int i = 1; i <= n; i += BUCK) {
        for(int j = 0; j <= n + 1; j++) {
            cnt1[j] = 0;
            sum1[j] = 0;
            nxt[j] = NMAX;
            ant[j] = -NMAX;
        }

        int sz = min(n,i + BUCK - 1) - i + 1;

        for(int j = i; j <= n && j < i + BUCK; j++) {
            sum1[values[j].second] = values[j].first;
            nv[j - i] = {values[j].second,{values[j].first,j - i + 1}};
        }

        for(int j = 1; j <= n; j++) {
            cnt1[j] = cnt1[j - 1] + (make_pair(v[j],j) < values[i]);
            sum1[j] = sum1[j - 1] + sum1[j];
            ant[j] = max(ant[j],ant[j - 1]);
        }

        for(int j = n; j >= 1; j--) {
            nxt[j] = min(nxt[j + 1],nxt[j]);
        }

        sort(nv,nv + sz);

        for(int i = 0; i < sz; i++) {
            ant[nv[i].first] = i;
            nxt[nv[i].first] = i;
        }

        for(int j = 1; j <= n; j++) {
            ant[j] = max(ant[j],ant[j - 1]);
        }

        for(int j = n; j >= 1; j--) {
            nxt[j] = min(nxt[j + 1],nxt[j]);
        }

        for(int j = 0; j < sz; j++) {
            dp[j][j] = nv[j].second.first;
            long long big_sum = 0,low_cnt = 1;

            for(int k = j - 1; k >= 0; k--) {
                if(nv[k].second.second > nv[j].second.second) {
                    big_sum += nv[k].second.first;
                }
                else {
                    low_cnt++;
                }
                dp[k][j] = dp[k][j - 1] + 2 * big_sum + 1LL * (2 * low_cnt - 1) * nv[j].second.first;
            }
        }

        for(int j = 1; j <= q; j++) {
            ans[j] += 2LL * (sum1[queries[j].second] - sum1[queries[j].first - 1]) * (cnt1[queries[j].second] - cnt1[queries[j].first - 1]);
            if(nxt[queries[j].first] == NMAX || ant[queries[j].second] == -NMAX || nxt[queries[j].first] > ant[queries[j].second]) {
                continue;
            }
            ans[j] += dp[nxt[queries[j].first]][ant[queries[j].second]];
        }
    }

    for(int i = 1; i <= q; i++) {
        cout << fixed << setprecision(10) << (double)ans[i] / ((double)(queries[i].second - queries[i].first + 1) * (queries[i].second - queries[i].first + 1)) << "\n";
    }

    return 0;
}