#include <fstream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXF = 30;
const int MAXT = 100000;

vector<int> level[MAXF];
bool out[1 + MAXT];
map<pair<int, pair<int, int> >, vector<int> > dp[MAXF];

int main() {
    freopen("fft2d.in", "r", stdin);
    freopen("fft2d.out", "w", stdout);
    int f, t, number = 0;
    scanf("%d%d", &f, &t);
    for (int i = 1; i <= t; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        level[a].push_back(b);
    }
    long long answer = 1LL << (2 * f - 2);
    for (int i = 0; i < f; i++) {
        sort(level[i].begin(), level[i].end());
        level[i].resize(unique(level[i].begin(), level[i].end()) - level[i].begin());
        for (auto &it : level[i]) {
            long long now = 1LL << (f - 1);
            int x = it;
            for (int j = 0; j < i; j++) {
                int second = x & ((1 << (f - 1 - j)) - 1), first = x - second;
                second = x & ((1 << (f - 1 - i)) - 1);
                for (auto &it : dp[j][make_pair(first, make_pair(second, f - 1 - i))])
                    if (!out[it])
                        now -= (1LL << (j + f - 1 - i));
            }
            answer -= now;
        }
        for (auto &it : level[i]) {
            int x = it;
            number++;
            for (int j = 0; j < i; j++) {
                int second = x & ((1 << (f - 1 - j)) - 1), first = x - second;
                second = x & ((1 << (f - 1 - i)) - 1);
                for (auto &it : dp[j][make_pair(first, make_pair(second, f - 1 - i))])
                    if (!out[it])
                        out[it] = true;
                dp[j][make_pair(first, make_pair(second, f - 1 - i))].clear();
            }
            for (int j = i; j < f; j++) {
                int second = x & ((1 << (f - 1 - i)) - 1), first = x - second;
                second = x & ((1 << (f - 1 - j)) - 1);
                dp[i][make_pair(first, make_pair(second, f - 1 - j))].push_back(number);
            }
        }
    }
    printf("%lld\n", answer);
    return 0;
}
