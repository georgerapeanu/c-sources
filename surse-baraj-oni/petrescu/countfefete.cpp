#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = fopen("countfefete.in", "r"), *fout = fopen("countfefete.out", "w");

#define MOD 1000000007

#define MAXN 200000

const long long MARE = 1LL * MOD * MOD;
int put[MAXN + 1];
int cnt[MAXN + 1], mask[MAXN + 1];
int v[MAXN + 1], p[MAXN + 1], t[MAXN + 1];
int ans;
std::vector < int > g[MAXN + 1];

bool cmp(const int &a, const int &b) {
    if (v[a] != v[b]) return v[a] > v[b];
    else return a > b;
}

inline void vezi(int x, int val, int add) {
    if (add == -1) {
        for (int i = 0; i < 30; i++) {
            if ((mask[x] & (1 << i)) == 0 && (val & (1 << i))) {
                ans = (ans + MARE - 1LL * put[i] * (put[cnt[x]] - 1)) % MOD;
                val ^= 1 << i;
            }
        }
    }
    ans = (ans + MARE + add * (1LL * mask[x] * put[cnt[x] - 1] - val)) % MOD;
}

int sef(int x) {
    if (t[x] == x) return x;
    else return t[x] = sef(t[x]);
}

inline void baga(int x) {
    t[x] = x;
    cnt[x] = 1;
    mask[x] = v[x];
    for (auto &y : g[x]) {
        if (t[y]) {
            int z = sef(y);
            vezi(z, v[x], -1);
            t[z] = x;
            cnt[x] += cnt[z];
            mask[x] |= mask[z];
        }
    }
    vezi(x, v[x], 1);
}

int main() {
    int n;
    fscanf(fin, "%d", &n);

    put[0] = 1;
    for (int i = 1; i <= n; i++) {
        fscanf(fin, "%d", &v[i]);
        p[i] = i;
        put[i] = 2 * put[i - 1];
        if (put[i] >= MOD)
            put[i] -= MOD;
    }
    for (int i = n + 1; i <= 30; i++) {
        put[i] = 2 * put[i - 1];
        if (put[i] >= MOD)
            put[i] -= MOD;
    }

    std::sort(p + 1, p + n + 1, cmp);

    for (int i = 1; i < n; i++) {
        int x, y;
        fscanf(fin, "%d%d", &x, &y);

        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (int i = 1; i <= n; i++)
        baga(p[i]);

    fprintf(fout, "%d\n", ans);

    fclose(fin);
    fclose(fout);
    return 0;
}
